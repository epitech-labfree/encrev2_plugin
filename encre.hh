#ifndef _ENCRE_H
# define _ENCRE_H

#include <string>
#include <vector>
#include <boost/utility.hpp>
#include <vlc/vlc.h>

namespace encre
{
  class	Stream;

  enum e_action
    {
      NOTHING,
      STREAM,
      DISPLAY
    };

  template <typename T>
  class	Encre : public boost::noncopyable
  {

  private:
    T*						m_data;
    Stream*					m_stream;

    static const char*	DefaultArgs[];

  public :
    Encre();
    Encre(const std::vector<std::string>&	vlcOpts);

    bool					start();
    Stream*					getStream(e_action=NOTHING);
    T*						getData() const;
  };
}

#include "Stream.hh"

#endif // _ENCRE_H
