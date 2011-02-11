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
#include <stdlib.h>
#include <map>
#include <string>
#include "encrev2_vlc.hh"
//Allow PRId64 to be defined:
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <cstdio>
#include <boost/asio.hpp>
#include "network.hh"
#include "protocol.hh"

using namespace std;

Vlc::Vlc() : m_vlc(0), m_mp(0), m_m(0), m_window(0), _net(0),
	_vlc_args(new std::list<const char*>()) {

  std::clog << "Encre::Vlc, Initialization..." << std::endl;
  // init vlc modules, should be done only once

  _net = new Network();
  _vlc_args->push_back("-I");
  _vlc_args->push_back("dummy"); /* Don't use any interface */
  _vlc_args->push_back("--ignore-config"); /* Don't use VLC's config */
  _vlc_args->push_back("-vv");

  std::clog << "Encre::Vlc, ...Done!" << std::endl;
}

bool
Vlc::start() {
	if (m_vlc != 0)
		return false;

	const char* vlc_args[_vlc_args->size()];
	std::list<const char*>::iterator it = _vlc_args->begin();
	unsigned int i = 0;
	for ( ; it != _vlc_args->end(); ++it, ++i)
	{
		vlc_args[i] = (*it);
		std::cout << *it << std::endl;
	}
	m_vlc = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);
	std::clog << "Encre::Vlc, Starting" << std::endl;
	return m_vlc != 0;
}

Vlc::~Vlc()
{
  std::clog << "Encre::Vlc, Destruction" << std::endl;
  if (_net)
    delete _net;
  libvlc_media_player_release(m_mp);
  libvlc_release(m_vlc);
  delete _vlc_args;
}

bool          Vlc::set_window(FB::PluginWindow *win)
{
  if (win)
    std::clog << "Attaching to the window" << endl;
  else
    std::clog << "Detaching from the window" << endl;

  // VlcSystemStrategy::set_window(m_mp, win);
  m_window = win;

  return true;
}

bool		Vlc::init_stream(const std::string& label)
{
  if (good() == false)
    return false;

  _net->write(Protocol::put(label));

  std::string mrl;
  VlcSystemStrategy::get_webcam_mrl(mrl);
  m_m = libvlc_media_new_location(m_vlc, mrl.c_str()); // XXX: Never released
  std::clog << "Init streaming " << mrl << std::endl;
}

bool		Vlc::stream()
{
  if (good() == false)
    return false;

  if (m_m)
  {
    //addRuntimeOption(":sout=#transcode{vcodec=h264,vb=800,scale=1,acodec=mp4a,ab=128,channels=2,samplerate=44100}:smem{mux=ts}");
    //addRuntimeOption(":v4l2-caching=500");
    //addRuntimeOption(":sout-x264-tune=zerolatency");
    //addRuntimeOption(":sout-x264-tune=veryfast");
    setDataLockCallback(reinterpret_cast<void*>(&Vlc::lock));
    setDataUnlockCallback(reinterpret_cast<void*>(&Vlc::unlock));
    setDataCtx( this );
    //addRuntimeOption(":sout-transcode-width=400");
    //addRuntimeOption(":sout-transcode-height=400");
    //addRuntimeOption(":no-skip-frames");
    m_mp = libvlc_media_player_new(m_vlc);
    libvlc_media_player_set_media (m_mp, m_m);

    //play la video
    libvlc_media_player_play(m_mp);
  }
  std::clog << "Streaming " << std::endl;
  return true;
}

void	      Vlc::stop_stream() {
    libvlc_media_release(m_m);
    this->stop();
}

bool          Vlc::play(const std::string& label)
{
  if (good() == false)
    return false;

  _net->write(Protocol::get(label));

  m_m = libvlc_media_new_location(m_vlc, "imem://width=400:height=400:fps=30:cookie=0:codec=H264:cat=4:caching=0");
  if (m_m)
  {
    //addRuntimeOption(":input-slave=imem://cookie=1:cat=1:codec=mp4a:samplerate=44100:channels=2:caching=0");
    addRuntimeOption(":demux=ts");
    addRuntimeOption(":text-renderer dummy");
    m_mp = libvlc_media_player_new_from_media(m_m);

    setVideoGetCallback(reinterpret_cast<void*>(&getVideo));
    setVideoReleaseCallback(reinterpret_cast<void*>(&release));
    setImemDataCtx(this);

    //libvlc_media_release(m_m);
    VlcSystemStrategy::set_window(m_mp, m_window);
    libvlc_media_player_play(m_mp);
  }
  return true;
}

void
Vlc::stop() {
	std::clog << "Stop video" << std::endl;
	if (m_mp != 0)
		libvlc_media_player_stop(m_mp);
}

void
Vlc::addRuntimeOption(const char* opt)
{
  std::clog << "EncreVlc::addRuntimeOption " << opt << endl;
  libvlc_media_add_option_flag(m_m, opt, libvlc_media_option_trusted);
}

void
Vlc::addStartUpOption(const char* opt)
{
  std::clog << "EncreVlc::addStartUpOption " << opt << endl;
  _vlc_args->push_back(opt);
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
	     int size,
	     long dts )
{
  // c'est ici que l'on traite la video
  if (vlc && vlc->_net->isConnected())
    {
      //Network* net = Network::getInstance();
      vlc->_net->write(buffer, size);
      delete (char*)buffer;
    }
}

void
Vlc::lockAudio(Vlc* vlc, void** pp_ret,
	   int size)
{
  int * buffer = new int[size];
  *pp_ret = (void*)buffer;
}

void
Vlc::unlockAudio( Vlc* vlc, void* buffer,
	     int width, int height, int bpp, int size,
	     long pts )
{
  if (vlc && vlc->_net->isConnected())
    {
      // c'est ici que l'on traite le son
      //Network* net = Network::getInstance();
      vlc->_net->write(buffer, size);
      //boost::asio::write(vlc->getSocket(), boost::asio::buffer(buffer, size));
      delete (char*)buffer;
    }
}

int
Vlc::getVideo(void* data, const char* cookie, int64_t* dts, int64_t* pts,
			     unsigned* flags, size_t* len, void** buffer)
{
  Vlc	*myVlc = static_cast<Vlc*>(data);
  if (myVlc == 0)
    return -1;
  *buffer = new char [4096];
  *len = 0;
  //lecture sur le reseau
  //Network* net = Network::getInstance();
  *len = myVlc->_net->read(*buffer, 4096);
  //*len =  boost::asio::read(myVlc->getSocket(), boost::asio::buffer(*buffer, 4096));
  return (*len ? 0 : -1);
}

int
Vlc::release(void *data, const char *cookie, size_t, void *buffer)
{
  delete (char*)buffer;
  buffer = NULL;
  return 0;
}

// ---------------- Private Methods -----------------------

void
Vlc::setVideoLockCallback(void* callback)
{
  char    param[64];

  sprintf(param, ":sout-smem-video-prerender-callback=%"PRId64, (long long int)callback);
  addRuntimeOption(param);
}

void
Vlc::setVideoUnlockCallback(void* callback)
{
  char    param[64];

  sprintf(param, ":sout-smem-video-postrender-callback=%"PRId64, (long long int)callback);
  addRuntimeOption(param);
}

void
Vlc::setDataLockCallback(void* callback)
{
  char    param[64];

  sprintf(param, ":sout-smem-data-prerender-callback=%"PRId64, (long long int)callback);
  addRuntimeOption(param);
}

void
Vlc::setDataUnlockCallback(void* callback)
{
  char    param[64];

  sprintf(param, ":sout-smem-data-postrender-callback=%"PRId64, (long long int)callback);
  addRuntimeOption(param);
}

void
Vlc::setAudioLockCallback(void* callback)
{
  char    param[64];

  sprintf(param, ":sout-smem-audio-prerender-callback=%"PRId64, (long long int)callback);
  addRuntimeOption(param);
}

void
Vlc::setAudioUnlockCallback(void* callback)
{
  char    param[64];

  sprintf(param, ":sout-smem-audio-postrender-callback=%"PRId64, (long long int)callback);
  addRuntimeOption(param);
}

void
Vlc::setVideoGetCallback(void* callback)
{
  char    param[64];

  sprintf(param, ":imem-get=%"PRId64, (long long int)callback);
  addRuntimeOption(param);
}

void
Vlc::setVideoReleaseCallback(void* callback)
{
  char    param[64];

  sprintf(param, ":imem-release=%"PRId64, (long long int)callback);
  addRuntimeOption(param);
}

void
Vlc::setVideoDataCtx( void* dataCtx )
{
  char    param[64];
  sprintf( param, ":sout-smem-video-data=%"PRId64, (long long int)dataCtx );
  addRuntimeOption( param );
}

void
Vlc::setDataCtx( void* dataCtx )
{
  char    param[64];
  sprintf(param, ":sout-smem-video-data=%"PRId64, (long long int)dataCtx);
  addRuntimeOption(param);
  sprintf(param, ":sout-smem-audio-data=%"PRId64, (long long int)dataCtx);
  addRuntimeOption(param);
  sprintf(param, ":sout-smem-data-data=%"PRId64, (long long int)dataCtx);
  addRuntimeOption(param);
}

void
Vlc::setImemDataCtx( void* dataCtx )
{
  char    param[64];
  sprintf(param, ":imem-data=%"PRId64, (long long int)dataCtx);
  addRuntimeOption(param);
}
