#ifndef		_STREAM_H
# define	_STREAM_H

#include <boost/utility.hpp>
#include <string>
#include <vector>
#include <vlc/vlc.h>

namespace	vlc
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
    virtual bool			setOptions(std::vector<std::string>);
    virtual bool			setOptions(const std::string&);
    virtual bool			play();
    virtual bool			stop();

  protected :
    Stream() {}
    Stream(libvlc_media_player_t *mp);

    libvlc_media_player_t*		m_mp;
    libvlc_media_t*			m_media;
    e_state				m_state;
    //friend				class instance;
  };

}

#endif // _STREAM_H
