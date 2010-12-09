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

using namespace std;

static const char * const vlc_args[] = {
  "-I", "dummy", /* Don't use any interface */
  "--ignore-config", /* Don't use VLC's config */
  "-vvv"
};

// Exception mechanism has been removed in 1.1
// static void raise(libvlc_exception_t * ex)
// {
//   if (libvlc_exception_raised(ex))
//     cerr <<  "Encre::Vlc, Error: " << libvlc_exception_get_message(ex) << endl;
// }


Vlc::Vlc() : m_vlc(0), m_mp(0), m_m(0), m_window(0)
{
  cout << "Encre::Vlc, Initialization..." << endl;

  // init vlc modules, should be done only once
  m_vlc = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);

  cout << "Encre::Vlc, ...Done!" << endl;
}

Vlc::~Vlc()
{
  cout << "Encre::Vlc, Destruction" << endl;

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

void          Vlc::stream(std::string host, std::string port)
{
  std::string mrl;

  VlcSystemStrategy::get_webcam_mrl(mrl);
  cout << "Streaming " << mrl << " to " << host << ":" << port << endl;

  m_m = libvlc_media_new_path(m_vlc, mrl.c_str());
  if (m_m)
  {
    m_mp = libvlc_media_player_new_from_media(m_m);
    libvlc_media_release (m_m);
    VlcSystemStrategy::set_window(m_mp, m_window);
    libvlc_media_player_play(m_mp);
  }
}

void          Vlc::play(std::string mrl)
{
	std::clog << "Playing " << mrl << std::endl;

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
	std::clog << "Stop" << std::endl;
	return libvlc_media_player_stop(m_mp);
}

VlcCliOpt*
Vlc::getCliOpt() const {
	return m_vlc_cli_opt;
}

// Just wrappers
void
Vlc::set_option(const std::string& s1,
    const std::string&s2, const std::string&s3) {
	std::cout << "Vlc::set_option" << std::endl;
	m_vlc_cli_opt->set_option(s1,s2,s3);
}

std::string&
Vlc::get_option() {
	m_vlc_cli_opt->get_option();
}
