#include "Stream.hh"

namespace	vlc
{
  Stream::~Stream()
  {
  }

  Stream::e_state			Stream::state()
  {
    return (m_state);
  }
  
  bool		Stream::setOptions(std::vector<std::string>)
  {
    return (true);
  }

  bool		Stream::setOptions(const std::string&)
  {
    return (true);
  }

  bool		Stream::play()
  {
    return (true);
  }

  bool		Stream::stop()
  {
    return (true);
  }

  Stream::Stream(libvlc_media_player_t* mp)
  {
    m_mp = mp;
  }
}
