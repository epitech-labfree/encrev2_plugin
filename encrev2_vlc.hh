#ifndef _ENCRE_VLC_H
# define _ENCRE_VLC_H

#include <string>
#include <vector>
#include <boost/utility.hpp>
#include <vlc/vlc.h>

namespace vlc
{
class	Stream;
  class	Vlc : public boost::noncopyable
  {
  private:
    libvlc_instance_t*			m_vlc;
    Stream*				m_stream;

    static const char*	DefaultArgs[];

  public :
    Vlc();
    Vlc(const std::vector<std::string>&	vlcOpts);
    Stream*				getStream() const;
    friend				class Stream;
  };
}

#include "Stream.hh"

#endif // _ENCRE_VLC_H
