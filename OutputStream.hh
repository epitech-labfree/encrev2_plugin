#ifndef _OUTPUTSTREAM_H
# define _OUTPUTSTREAM_H

#include "Stream.hh"
#include "Smem.hh"
#include <boost/signals2.hpp>

namespace encre
{

  typedef boost::signals2::signal<unsigned int (const char *, unsigned int)> t_bsign;

  class	OutputStream : public Stream
  {
  private :
    Smem		m_imem;
    t_bsign		m_signal;
  public :
    t_bsign&		on_data_available();
    OutputStream();
  };
}

#endif // _OUTPUTSTREAM_H
