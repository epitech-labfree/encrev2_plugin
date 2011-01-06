/*
** encrev2_vlc.cpp
** Login : <elthariel@rincevent>
** Started on  Thu Sep 30 18:27:25 2010 elthariel
** $Id$
**
** Author(s):
**  - elthariel <elthariel@gmail.com>
**
** Copyright (C) 2010 elthariel
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#include <iostream>
#include <map>
#include <string>
#include "encrev2_vlc.hh"
//Allow PRId64 to be defined:
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <cstdio>
#include "Jingle.hh"

using namespace std;

static const char * vlc_args[] = {
  "-I", "dummy", /* Don't use any interface */
  "--ignore-config", /* Don't use VLC's config */
  "-vv",
  "--sout", 0, /* Left this empty for the --sout option */
};

// Exception mechanism has been removed in 1.1
// static void raise(libvlc_exception_t * ex)
// {
//   if (libvlc_exception_raised(ex))
//     cerr <<  "Encre::Vlc, Error: " << libvlc_exception_get_message(ex) << endl;
// }


Vlc::Vlc() : m_vlc(0), m_mp(0), m_m(0), m_window(0), _opt()
{
  cout << "Encre::Vlc, Initialization..." << endl;
  // init vlc modules, should be done only once
  m_vlc = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);
  //m_vlc = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);
  cout << "Encre::Vlc, ...Done!" << endl;
}

Vlc::~Vlc()
{
  cout << "Encre::Vlc, Destruction" << endl;
  libvlc_event_detach(m_me, libvlc_MediaPlayerPlaying, callback, this);
  libvlc_release(m_vlc);
}

bool	      Vlc::start()
{
	if (m_vlc != 0)
		return false;

	std::cout << "Start vlc with :" << std::endl;
	vlc_args[5] = get_option()->c_str();

	for (int i = 0; i != sizeof(vlc_args) / sizeof(vlc_args[0]); ++i)
		std::cout << "- " << vlc_args[i] << std::endl;

	m_vlc = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);
	return m_vlc != 0;
}

bool          Vlc::set_window(FB::PluginWindow *win)
{
  if (win)
    cout << "Attaching to the window" << endl;
  else
    cout << "Detaching from the window" << endl;

  // VlcSystemStrategy::set_window(m_mp, win);
  m_window = win;

  return true;
}

void
Vlc::setVideoDataCtx( void* dataCtx )
{
  char    param[64];
  sprintf( param, ":sout-smem-video-data=%"PRId64, (intptr_t)dataCtx );
  addOption( param );
}

#include <stdlib.h>
bool		Vlc::stream(std::string host, std::string port)
{
  std::string mrl;

  if (m_vlc == 0)
    return false;
  VlcSystemStrategy::get_webcam_mrl(mrl);
  m_m = libvlc_media_new_location(m_vlc, mrl.c_str());
  std::cout << "Streaming " << mrl << " to " << host << ":" << port << std::endl;

  if (m_m)
  {
    addOption(":sout=#transcode{}:smem");
    addOption(":v4l2-caching=500");
    setVideoDataCtx( this );
    setVideoLockCallback(reinterpret_cast<void*>(&lock));
    setVideoUnlockCallback(reinterpret_cast<void*>(&unlock));
    addOption(":sout-transcode-vcodec=RV16");
    addOption(":sout-transcode-width=400");
    addOption(":sout-transcode-height=400");
    addOption(":no-skip-frames");
    m_mp = libvlc_media_player_new(m_vlc);
    libvlc_media_player_set_media (m_mp, m_m);

    m_me = libvlc_media_player_event_manager(m_mp);
    put_events();
    cout << "event : " << (int64_t)m_me << endl;
    //play la video
    libvlc_media_player_play(m_mp);
  }
  return true;
}

bool          Vlc::play()
{
  if (m_vlc == 0)
    return false;
  std::clog << "Playing " << "imem://" << std::endl;
  m_m = libvlc_media_new_location(m_vlc, "imem://");
  if (m_m)
  {
    m_mp = libvlc_media_player_new_from_media(m_m);

    setVideoGetCallback(reinterpret_cast<void*>(&getVideo));
    setVideoReleaseCallback(reinterpret_cast<void*>(&release));
    addOption("imem-width=400");
    addOption("imem-height=400");

    libvlc_media_release(m_m);
    VlcSystemStrategy::set_window(m_mp, m_window);
    libvlc_media_player_play(m_mp);
  }
  return true;
}

void
Vlc::stop() {
	std::clog << "Stop" << std::endl;
	if (m_mp != 0)
		libvlc_media_player_stop(m_mp);
}

// TODO: Utiliser libvlc_media_add_option_flag

void
Vlc::set_option(const std::string& global_option,
    const std::string& option, const std::string& value) {
	std::multimap<std::string, std::string>::iterator it = _opt.find(global_option);
	std::string key(option.c_str());
	key.append("=");
	key.append(value.c_str());

	for (; it != _opt.end(); ++it) {
		if ((*it).second.substr(0, (*it).second.find("=")) == option) {
			(*it).second = key;
			return ;
		}
	}
	_opt.insert(std::pair<std::string, std::string>(global_option, key));
}

std::string*
Vlc::get_option() {
	std::string* str = new std::string("#");
	std::multimap<std::string, std::string>::iterator it = _opt.begin();

	if (_opt.empty())
		return (new std::string(""));

	while (it != _opt.end()) {
		unsigned int count = _opt.count((*it).first);
		str->append((*it).first);
		str->append("{");

		for (unsigned int i = 0; i != count; ++i, ++it) {
			str->append((*it).second);
			if ((i+1) != count)
				str->append(",");
		}
		str->append("}");
	}
	std::clog << *str << std::endl;
	return str;
}

void
Vlc::reset_option() {
	_opt.clear();
}

void
Vlc::setVideoLockCallback(void* callback)
{
  char    param[64];

  sprintf(param, ":sout-smem-video-prerender-callback=%"PRId64, (intptr_t)callback);
  addOption(param);
}

void
Vlc::setVideoUnlockCallback(void* callback)
{
  char    param[64];

  sprintf(param, ":sout-smem-video-postrender-callback=%"PRId64, (intptr_t)callback);
  addOption(param);
}

void
Vlc::setAudioLockCallback(void* callback)
{
  char    param[64];

  sprintf(param, ":sout-smem-audio-prerender-callback=%"PRId64, (intptr_t)callback);
  addOption(param);
}

void
Vlc::setAudioUnlockCallback(void* callback)
{
  char    param[64];

  sprintf(param, ":sout-smem-audio-postrender-callback=%"PRId64, (intptr_t)callback);
  addOption(param);
}

void
Vlc::addOption( const char* opt )
{
  cout << "EncreVlc::addOption " << opt << endl;
  libvlc_media_add_option_flag(m_m, opt, libvlc_media_option_trusted);
}

void
Vlc::put_events()
{
  libvlc_event_attach(m_me, libvlc_MediaPlayerPlaying, callback, this);
}

void
Vlc::callback(const libvlc_event_t* event, void* ptr)
{
  Vlc*	self = reinterpret_cast<Vlc*>(ptr);

  cout << "Media player playing" << endl;
  //self->playd();
}

void
Vlc::playd()
{
  libvlc_media_player_play(m_mp);
}

void
Vlc::lock(Vlc* vlc, void** pp_ret,
	   int size)
{
  int * buffer = new int[size];
  *pp_ret = (void*)buffer;
}

void
Vlc::unlock( Vlc* vlc, void* buffer,
	     int width, int height, int bpp, int size,
	     long pts )
{
  //ici qu'on traite la video
}

int
Vlc::getVideo(void* data, const char* cookie, int64_t* dts, int64_t* pts,
			     unsigned* flags, size_t* len, void** buffer)
{
}

void
Vlc::release(void *data, const char *cookie, size_t, void *)
{
}

void
Vlc::setVideoGetCallback(void* callback)
{
  char    param[64];

  sprintf(param, ":imem-get=%"PRId64, (intptr_t)callback);
  addOption(param);
}

void
Vlc::setVideoReleaseCallback(void* callback)
{
  char    param[64];

  sprintf(param, ":imem-release=%"PRId64, (intptr_t)callback);
  addOption(param);
}
