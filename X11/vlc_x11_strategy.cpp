/*
** vlc_x11_strategy.cpp
** Login : <elthariel@rincevent>
** Started on  Fri Oct  1 02:15:32 2010 elthariel
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
#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include "X11/PluginWindowX11.h"
#include "vlc_system_strategy.hh"

using namespace std;

void            VlcSystemStrategy::set_window(libvlc_media_player_t *mp,
                                              FB::PluginWindow *w)
{
  if (w && mp)
  {
    FB::PluginWindowX11 *x11 = w->get_as<FB::PluginWindowX11>();

    cout << "Xid = " << x11->getWindow() << endl;

    libvlc_media_player_set_xwindow(mp, (uint32_t)x11->getWindow());
  }
  else if (mp)
    libvlc_media_player_set_xwindow(mp, (uint32_t)0);
}

bool             VlcSystemStrategy::get_webcam_mrl(std::string &mrl)
{
  mrl = "v4l2:///dev/video0:alsa://plughw:0,0";
  return (true);
}

