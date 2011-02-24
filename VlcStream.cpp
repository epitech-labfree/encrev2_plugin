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
	if (m_state != Stream::ACTIVE)
	  {
	    if (m_media)
	      libvlc_media_add_option_flag(m_media, (*it).c_str(), libvlc_media_option_trusted);
	    else
	      return (false);
	  }
	else
	  opt += (*it);
      }
    return (true);
  }

  bool		VlcStream::setOptions(const std::string& opts)
  {
    if (m_state != Stream::ACTIVE)
      {
	if (m_media)
	  {
	    libvlc_media_add_option_flag(m_media, opts.c_str(), libvlc_media_option_trusted);
	    return (true);
	  }
	else
	  return (false);
      }
    else
      opt += opts;
    return (true);
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
	libvlc_media_release(m_media);
	m_media = 0;
      }
    return (true);
  }

  VlcStream::VlcStream(Encre<libvlc_instance_t>* encre, libvlc_media_player_t* mp) : Stream(encre), m_media(0)
  {
    m_mp = mp;
  }

  VlcStream::VlcStream(Encre<libvlc_instance_t>* encre) : Stream(encre), m_media(0)
  {
  }
}
