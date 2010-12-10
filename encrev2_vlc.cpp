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
  //m_vlc = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);

  cout << "Encre::Vlc, ...Done!" << endl;
}

Vlc::~Vlc()
{
  cout << "Encre::Vlc, Destruction" << endl;

  libvlc_release(m_vlc);
}

void	      Vlc::start()
{
	if (m_vlc != 0)
		return ;

	std::cout << "Start vlc with :" << std::endl;
	vlc_args[5] = get_option()->c_str();

	for (int i = 0; i != sizeof(vlc_args) / sizeof(vlc_args[0]); ++i)
		std::cout << "- " << vlc_args[i] << std::endl;

	m_vlc = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);
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

bool          Vlc::stream(std::string host, std::string port)
{
  std::string mrl;

  if (m_vlc == 0)
    return false;
  VlcSystemStrategy::get_webcam_mrl(mrl);
  std::cout << "Streaming " << mrl << " to " << host << ":" << port << std::endl;
  m_m = libvlc_media_new_path(m_vlc, mrl.c_str());
  if (m_m)
  {
    m_mp = libvlc_media_player_new_from_media(m_m);
    libvlc_media_release (m_m);
    VlcSystemStrategy::set_window(m_mp, m_window);
    libvlc_media_player_play(m_mp);
  }
  return true;
}

bool          Vlc::play(std::string mrl)
{
  if (m_vlc == 0)
    return false;
  std::clog << "Playing " << mrl << std::endl;
  m_m = libvlc_media_new_path(m_vlc, mrl.c_str());
  if (m_m)
  {
    m_mp = libvlc_media_player_new_from_media(m_m);
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
