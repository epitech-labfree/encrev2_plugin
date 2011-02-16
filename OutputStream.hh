#ifndef _OUTPUTSTREAM_H
# define _OUTPUTSTREAM_H

#include "Stream.hh"

namespace vlc
{

  typedef t_bsign boost::signals2::signal<uin32_t (const char *, uin32_t)>

  class	OutputStream : public Stream
  {
  private :
    Imem		m_imem;
    t_bsign		m_signal;
  public :
    t_bsign&		on_data_available();
  };
}

#endif // _OUTPUTSTREAM_H
