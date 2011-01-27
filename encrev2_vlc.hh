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

# include <string>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
# include <map>
#include <boost/asio.hpp>
# include "vlc_system_strategy.hh"

class Vlc
{
public:
  Vlc();
  ~Vlc();

  bool          set_window(FB::PluginWindow *win);
  bool          stream();
  bool          play();
  void		stop();
  void		addOption(const char* opt);
  void		connect(const std::string&, const std::string&);
  void		disconnect();

  boost::asio::ip::tcp::socket& getSocket() const;

  static void	lock(Vlc* clipWorkflow, void**, int);
  static void	unlock(Vlc* clipWorkflow, void* buffer,
			     int size,
			     long pts);
  static void	lockAudio(Vlc* clipWorkflow, void**, int);
  static void	unlockAudio(Vlc* clipWorkflow, void* buffer,
			     int width, int height, int bpp, int size,
			     long pts);

  static int	getVideo(void *data, const char *cookie, int64_t *dts, int64_t *pts,
			     unsigned *flags, size_t *, void **);
  static int	release(void *data, const char *cookie, size_t, void *);

private:
  void		setVideoLockCallback(void* callback);
  void		setVideoUnlockCallback(void* callback);
  void		setDataLockCallback(void* callback);
  void		setDataUnlockCallback(void* callback);
  void		setAudioLockCallback(void* callback);
  void		setAudioUnlockCallback(void* callback);
  void		setVideoDataCtx(void*);
  void		setVideoReleaseCallback(void*);
  void		setVideoGetCallback(void*);
  void		setDataCtx(void*);
  void		setImemDataCtx(void*);

protected:
  libvlc_instance_t		*m_vlc;
  libvlc_media_player_t		*m_mp;
  libvlc_media_t		*m_m;
  FB::PluginWindow		*m_window;
  boost::asio::ip::tcp::socket*	_socket;
  bool				_is_connected;
};

#endif	    /* !ENCREV2_VLC_HH_ */
