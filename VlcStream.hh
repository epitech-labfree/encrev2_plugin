#ifndef		_VLCSTREAM_H
# define	_VLCSTREAM_H

#include <boost/utility.hpp>
#include <string>
#include <vector>
#include <vlc/vlc.h>

#include "encre.hh"
#include "Stream.hh"

namespace	encre
{
  class VlcStream : public Stream
  {
  public :
    virtual				~VlcStream();

    virtual bool			setOptions(const std::vector<std::string>&);
    virtual bool			setOptions(const std::string&);
    virtual bool			play();
    virtual bool			stop();

    VlcStream(Encre<libvlc_instance_t>*);
    VlcStream(Encre<libvlc_instance_t>*, libvlc_media_player_t *mp);

  protected :
    libvlc_media_player_t*		m_mp;
    libvlc_media_t*			m_media;
    std::string				opt;
  };

}

#endif // _VLCSTREAM_H
