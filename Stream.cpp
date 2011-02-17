#include "Stream.hh"

namespace	encre
{
  Stream::~Stream()
  {
    stop();
  }

  Stream::e_state			Stream::state()
  {
    return (m_state);
  }
  
  bool		Stream::setOptions(const std::vector<std::string>& opts)
  {
    std::vector<std::string>::const_iterator it = opts.begin();
    std::vector<std::string>::const_iterator ite = opts.end();

    for (; it != ite; ++it)
      {
	libvlc_media_add_option_flag(m_media, (*it).c_str(), libvlc_media_option_trusted);
      }
    return (true);
  }

  bool		Stream::setOptions(const std::string& opts)
  {
    if (m_state != ACTIVE)
      {
	libvlc_media_add_option_flag(m_media, opts.c_str(), libvlc_media_option_trusted);
	return (true);
      }
    return (false);
  }

  bool		Stream::play()
  {
    return (libvlc_media_player_play(m_mp) == 0);
  }

  bool		Stream::stop()
  {
    if (m_mp != 0)
      {
	libvlc_media_player_stop(m_mp);
	m_mp = 0;
      }
    return (true);
  }

  Stream::Stream(libvlc_media_player_t* mp)
  {
    m_mp = mp;
  }

  Stream::Stream()
  {
    m_mp = libvlc_media_player_new(m_encre->m_vlc);
  }
}
