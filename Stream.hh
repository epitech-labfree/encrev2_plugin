#ifndef		_STREAM_H
# define	_STREAM_H

#include <boost/utility.hpp>
#include <string>
#include <vector>
#include <vlc/vlc.h>

#include "encre.hh"

namespace	encre
{
  class Stream : public boost::noncopyable
  {
  public:

    enum e_state
      {
        ACTIVE,				// not configurable anymore
					// you should stop it before changing options
        INACTIVE			// configurable
      };
    virtual				~Stream();

    virtual e_state			state();
    // This method returns a bool because some parameters may not
    // fulfill security policies.
    virtual bool			setOptions(const std::vector<std::string>&) = 0;
    virtual bool			setOptions(const std::string&) = 0;
    virtual bool			play() = 0;
    virtual bool			stop() = 0;

    Stream();

  protected :
    Encre<libvlc_instance_t>*		m_encre;
    e_state				m_state;
  };

}

#endif // _STREAM_H
