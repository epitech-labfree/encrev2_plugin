#ifndef _ENCRE_H
# define _ENCRE_H

#include <string>
#include <vector>
#include <boost/utility.hpp>
#include <vlc/vlc.h>

namespace encre
{
  class	Stream;

  template <typename T>
  class	Encre : public boost::noncopyable
  {
  private:
    T*						m_vlc;
    Stream*					m_stream;

    static const char*	DefaultArgs[];

  public :
    Encre();
    Encre(const std::vector<std::string>&	vlcOpts);

    bool					start();
    Stream*					getStream() const;
    friend					class Stream;
    friend					class VlcStream;
  };
}

#include "Stream.hh"

#endif // _ENCRE_H
