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

using namespace std;

static const char * vlc_args[] = {
  "-I", "dummy", /* Don't use any interface */
  "--ignore-config", /* Don't use VLC's config */
  "-vv"
};

Vlc::Vlc() : m_vlc(0), m_mp(0), m_m(0), m_window(0), _is_connected(false)
{
  std::clog << "Encre::Vlc, Initialization..." << std::endl;
  // init vlc modules, should be done only once
  m_vlc = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);
  std::clog << "Encre::Vlc, ...Done!" << std::endl;
}

Vlc::~Vlc()
{
  std::clog << "Encre::Vlc, Destruction" << std::endl;
  libvlc_event_detach(m_me, libvlc_MediaPlayerPlaying, callback, this);
  libvlc_media_player_release(m_mp);
  libvlc_release(m_vlc);
}

void	      Vlc::connect() {
	if (_is_connected == true)
		return;

	std::clog << "Encre::Vlc, Connection" << std::endl;
	using boost::asio::ip::tcp;
	try {
	boost::asio::io_service io_service;
	tcp::resolver resolver(io_service);
	tcp::resolver::query query(tcp::v4(), "localhost", "4242");
	tcp::resolver::iterator iterator = resolver.resolve(query);
	_socket = new tcp::socket(io_service);
	_socket->connect(*iterator);
	}
	catch (...) {
		std::cerr << "Encre::Vlc, Enable to connect" << std::endl;
		return ;
	}
	_is_connected = true;
}

void	      Vlc::disconnect() {
	if (_is_connected == false)
		return ;
	_is_connected = false;
	_socket->close();
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

bool		Vlc::stream(std::string host, std::string port)
{
  if (_is_connected == false)
  {
    std::clog << "Encre::Vlc, Error: Not connected " << std::endl;
    return false;
  }
  std::string mrl;
  char request[] = "PUT toto\n\n";
  boost::asio::write(*_socket, boost::asio::buffer(request, sizeof(request)));

  if (m_vlc == 0)
    return false;
  VlcSystemStrategy::get_webcam_mrl(mrl);
  m_m = libvlc_media_new_location(m_vlc, mrl.c_str());
  std::clog << "Streaming " << mrl << " to " << host << ":" << port << std::endl;
  if (m_m)
  {
    //vcodec=h264,vb=800,scale=1,acodec=mp4a,ab=128,channels=2,samplerate=44100
    addOption(":sout=#transcode{}:smem");
    addOption(":v4l2-caching=500");
    setVideoLockCallback(reinterpret_cast<void*>(&Vlc::lock));
    setVideoUnlockCallback(reinterpret_cast<void*>(&Vlc::unlock));
    setDataCtx( this );
    // setAudioLockCallback(reinterpret_cast<void*>(&lockAudio));
    // setAudioUnlockCallback(reinterpret_cast<void*>(&unlockAudio));
    addOption(":sout-transcode-vcodec=RV16");
    addOption(":sout-transcode-width=400");
    addOption(":sout-transcode-height=400");
    addOption(":no-skip-frames");
    m_mp = libvlc_media_player_new(m_vlc);
    libvlc_media_player_set_media (m_mp, m_m);

    m_me = libvlc_media_player_event_manager(m_mp);
    put_events();
    //play la video
    libvlc_media_player_play(m_mp);
  }
  std::clog << "event : " << (int64_t)m_me << endl;
  return true;
}

bool          Vlc::play()
{
  if (_is_connected == false)
  {
    std::clog << "Encre::Vlc, Error: Not connected " << std::endl;
    return true;
  }

  char request[] = "GET /toto";
  boost::asio::write(*_socket, boost::asio::buffer(request, sizeof(request)));

  if (m_vlc == 0)
    return false;
  std::clog << "Playing " << "imem://width=400:height=400:fps=30:cookie=0:codec=H264:cat=4:caching=0" << std::endl;
  m_m = libvlc_media_new_location(m_vlc, "imem://width=400:height=400:fps=30:cookie=0:codec=H264:cat=4:caching=0");
  if (m_m)
  {
    m_mp = libvlc_media_player_new_from_media(m_m);

    addOption(":input-slave=imem://cookie=1:cat=1:codec=mp4a:samplerate=44100:channels=2:caching=0");
    setVideoGetCallback(reinterpret_cast<void*>(&getVideo));
    setVideoReleaseCallback(reinterpret_cast<void*>(&release));
    setImemDataCtx(this);
    // addOption(":imem-codec=h264");
    // addOption(":imem-width=400");
    // addOption(":imem-height=400");
    // addOption(":imem-fps=1");

    addOption(":text-renderer dummy");
    
    //addOption(":imem-cat=4");    

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

void
Vlc::addOption( const char* opt )
{
  std::clog << "EncreVlc::addOption " << opt << endl;
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

  std::clog << "Media player playing" << endl;
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

#include <stdio.h>
void
Vlc::unlock( Vlc* vlc, void* buffer,
	     int width, int height, int bpp, int size,
	     long pts )
{
  // c'est ici que l'on traite la video
  if (vlc->_is_connected)
    {
      char *toto = reinterpret_cast<char*>(buffer);
      printf("Gniarffffffffffffff%d %d\n", (int)buffer, toto[0]);
      boost::asio::write(vlc->getSocket(), boost::asio::buffer(buffer, size));
    }
}

void
Vlc::lockAudio(Vlc* vlc, void** pp_ret,
	   int size)
{
  int * buffer = new int[size * size];
  *pp_ret = (void*)buffer;
}

void
Vlc::unlockAudio( Vlc* vlc, void* buffer,
	     int width, int height, int bpp, int size,
	     long pts )
{
  // c'est ici que l'on traite le son
  delete buffer;
}

int
Vlc::getVideo(void* data, const char* cookie, int64_t* dts, int64_t* pts,
			     unsigned* flags, size_t* len, void** buffer)
{
  Vlc	*myVlc = static_cast<Vlc*>(data);
  *buffer = new char [4096];
  *len = 0;
  //lecture sur le reseau
  //*len =  boost::asio::read(myVlc->getSocket(), boost::asio::buffer(*buffer, 4096));
  return (*len ? 0 : -1);
}

boost::asio::ip::tcp::socket&
Vlc::getSocket() const {
	return *_socket;
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
	
void
Vlc::setVideoDataCtx( void* dataCtx )
{
  char    param[64];
  sprintf( param, ":sout-smem-video-data=%"PRId64, (intptr_t)dataCtx );
  addOption( param );
}

void
Vlc::setDataCtx( void* dataCtx )
{
  char    param[64];
  sprintf(param, ":sout-smem-video-data=%"PRId64, (intptr_t)dataCtx);
  addOption(param);
  sprintf(param, ":sout-smem-audio-data=%"PRId64, (intptr_t)dataCtx);
  addOption(param);
}

void
Vlc::setImemDataCtx( void* dataCtx )
{
  char    param[64];
  sprintf(param, ":imem-data=%"PRId64, (intptr_t)dataCtx);
  addOption(param);
}
