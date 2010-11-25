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
  "-v"
};

// Exception mechanism has been removed in 1.1
static void raise(libvlc_exception_t * ex)
{
  if (libvlc_exception_raised(ex))
    cerr <<  "Encre::Vlc, Error: " << libvlc_exception_get_message(ex) << endl;
}


Vlc::Vlc()
  :m_vlc(0), m_mp(0), m_m(0)
{
  cout << "Encre::Vlc, Initialization..." << endl;

  libvlc_exception_init(&m_ex);

  // init vlc modules, should be done only once
  m_vlc = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args, &m_ex);
  raise (&m_ex);
  if (m_vlc)
    {
      m_mp = libvlc_media_player_new(m_vlc, &m_ex);
      raise (&m_ex);
    }

  cout << "Encre::Vlc, ...Done!" << endl;
}

Vlc::~Vlc()
{
  cout << "Encre::Vlc, Destruction" << endl;

  libvlc_release(m_vlc);
  raise (&m_ex);
}

bool          Vlc::attach_window(FB::PluginWindow *win)
{
  cout << "Attaching to the window" << endl;
  VlcSystemStrategy::set_window(m_mp, win);
  //  if (win)
  //cout << "Attaching to the window" << endl;
  //else
  // cout << "Detaching from the window" << endl;

  // VlcSystemStrategy::set_window(m_mp, win);
  //m_window = win;

  return true;
}

bool          Vlc::detach_window(FB::PluginWindow *win)
//void          Vlc::stream(std::string host, std::string port)
{
  cout << "Detaching from the window" << endl;
  VlcSystemStrategy::set_window(m_mp, 0);   
  return true;
}
