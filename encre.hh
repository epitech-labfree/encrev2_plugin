#ifndef _ENCRE_H
# define _ENCRE_H

#include "vlc_system_strategy.hh"
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
  public:
    Encre();
    Encre(const std::vector<std::string>&	vlcOpts);
    virtual ~Encre();

    virtual void				set_window(FB::PluginWindow*);

    bool					start();
    T*						getData();
    Stream*					getStream(e_action=NOTHING);
    std::string*				getHostname();

  private:
    T*						m_data;
    Stream*					m_stream;

  public:
    FB::PluginWindow*				m_window;
    std::string*				m_host;
    short					m_port;
  };
}

#endif // _ENCRE_H
