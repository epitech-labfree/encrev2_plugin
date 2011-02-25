#include "VlcStream.hh"
#include <iostream>

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
	  opt += (*it);
      }
    if (m_state != Stream::ACTIVE)
      {
	if (m_media)
	  libvlc_media_add_option_flag(m_media, (*it).c_str(), libvlc_media_option_trusted);
	else
	  return (false);
      }
    return (true);
  }

  bool		VlcStream::setOptions(const std::string& opts)
  {
    opt += opts;
    if (m_state != Stream::ACTIVE)
      {
	if (m_media)
	  {
	    std::cout << "opt=" << opt << std::endl;
	    libvlc_media_add_option_flag(m_media, opt.c_str(), libvlc_media_option_trusted);
	    opt = "";
	    return (true);
	  }
	else
	  return (false);
      }
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
