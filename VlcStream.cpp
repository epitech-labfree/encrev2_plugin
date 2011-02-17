#include "VlcStream.hh"

namespace	encre
{
  VlcStream::~VlcStream()
  {
    stop();
  }
  
  bool		VlcStream::setOptions(const std::vector<std::string>& opts)
  {
    std::vector<std::string>::const_iterator it = opts.begin();
    std::vector<std::string>::const_iterator ite = opts.end();

    for (; it != ite; ++it)
      {
	libvlc_media_add_option_flag(m_media, (*it).c_str(), libvlc_media_option_trusted);
      }
    return (true);
  }

  bool		VlcStream::setOptions(const std::string& opts)
  {
    if (m_state != Stream::ACTIVE)
      {
	libvlc_media_add_option_flag(m_media, opts.c_str(), libvlc_media_option_trusted);
	return (true);
      }
    return (false);
  }

  bool		VlcStream::play()
  {
    return (libvlc_media_player_play(m_mp) == 0);
  }

  bool		VlcStream::stop()
  {
    if (m_mp != 0)
      {
	libvlc_media_player_stop(m_mp);
	m_mp = 0;
      }
    return (true);
  }

  VlcStream::VlcStream(libvlc_media_player_t* mp)
  {
    m_mp = mp;
  }

  VlcStream::VlcStream()
  {
    m_mp = libvlc_media_player_new(m_encre->m_vlc);
  }
}
