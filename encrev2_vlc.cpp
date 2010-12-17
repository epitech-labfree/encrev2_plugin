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
#include "encrev2_vlc.hh"
//Allow PRId64 to be defined:
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <cstdio>
#include "Jingle.hh"

using namespace std;

static const char * const vlc_args[] = {
  "",
  "--no-disable-screensaver",
  "--no-skip-frames",
  "-vvv"
};

Vlc::Vlc() : m_vlc(0), m_mp(0), m_m(0), m_window(0)
{
  cout << "Encre::Vlc, Initialization..." << endl;

  // init vlc modules, should be done only once
  m_vlc = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);
  Jingle j;
  cout << "Encre::Vlc, ...Done!" << endl;
}

Vlc::~Vlc()
{
  cout << "Encre::Vlc, Destruction" << endl;
  libvlc_event_detach(m_me, libvlc_MediaPlayerPlaying, callback, this);
  libvlc_release(m_vlc);
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
void          Vlc::stream(std::string host, std::string port)
{
  std::string mrl;

  VlcSystemStrategy::get_webcam_mrl(mrl);
  cout << "Streaming " << mrl << " to " << host << ":" << port << endl;
  m_m = libvlc_media_new_location(m_vlc, mrl.c_str());
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
}

void          Vlc::play(std::string mrl)
{
  std::cout << "Playing " << mrl << std::endl;

  m_m = libvlc_media_new_path(m_vlc, mrl.c_str());
  if (m_m)
  {
    m_mp = libvlc_media_player_new_from_media(m_m);

    libvlc_media_release(m_m);
    VlcSystemStrategy::set_window(m_mp, m_window);
    libvlc_media_player_play(m_mp);
  }
}

void
Vlc::stop() {
	std::cout << "Stop" << std::endl;
	return libvlc_media_player_stop(m_mp);
}

VlcCliOpt*
Vlc::getCliOpt() const {
	return m_vlc_cli_opt;
}

// Just a wrapper
void
Vlc::set_option(const std::string& s1,
    const std::string&s2, const std::string&s3) {
	std::clog << "Vlc" << std::endl;
	m_vlc_cli_opt->set_option(s1,s2,s3);
	std::clog << "END:Vlc" << std::endl;
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
  cout << "coucou" << size << endl;
  *pp_ret = (void*)buffer;
}

void
Vlc::unlock( Vlc* vlc, void* buffer,
	     int width, int height, int bpp, int size,
	     long pts )
{
  cout << "coucou2 " << buffer << endl;
}
