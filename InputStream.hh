#ifndef _INPUTSTREAM_H
# define _INPUTSTREAM_H

#include "Stream.hh"

namespace vlc
{

  typedef t_bsign boost::signals2::signal<uin32_t (const char *, uin32_t)>

  class	InputStream : public Stream
  {
  private :
    Imem		m_imem;
    t_bsign		m_signal;
  public :
    t_bsign&		on_data_needed();
  };
}

#endif // _INPUTSTREAM_H
