#ifndef		_STREAM_H
# define	_STREAM_H

#include <boost/utility.hpp>

namespace	vlc
{
  class Stream : public boost::noncopyable
  {
  public:
    enum state
      {
        ACTIVE,				// not configurable anymore
					// you should stop it before changing options
        INACTIVE			// configurable
      };
    virtual				~stream();

    virtual state			state();
    // This method returns a bool because some parameters may not
    // fulfill security policies.
    virtual bool			set_options(std::vector<std::string>);
    virtual bool			play();
    virtual bool			stop();


  protected :
    Stream() {}
    Stream(libvlc_media_player_t *mp);

    libvlc_media_player_t*		m_mp;
    libvlc_media_t*			m_media;
    state				m_state;
    //friend				class instance;
  };

}

#endif // _STREAM_H
