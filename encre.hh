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
      NOTHING=0,
      STREAM=1,
      DISPLAY=2
    };

  template <typename T>
  class	Encre
  {
  private:
    T*						m_data;
    Stream*					m_stream;

  public :
    Encre();
    Encre(const std::vector<std::string>&	vlcOpts);

    bool					start();
    T*						getData();
    Stream*					getStream(e_action=NOTHING);
  };
}

#endif // _ENCRE_H
