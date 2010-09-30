/*
** encrev2_vlc.hh
** Login : <elthariel@rincevent>
** Started on  Thu Sep 30 18:27:40 2010 elthariel
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

#ifndef   	ENCREV2_VLC_HH_
# define   	ENCREV2_VLC_HH_

# include <vlc/vlc.h>

class Vlc
{
public:
  Vlc();
  ~Vlc();

protected:
  libvlc_exception_t          m_ex;
  libvlc_instance_t           *m_vlc;
  libvlc_media_player_t       *m_mp;
  libvlc_media_t              *m_m;
  //void                        *m_handle;
};

#endif	    /* !ENCREV2_VLC_HH_ */
