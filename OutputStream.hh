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
    void		lock(Stream* stream, void** pp_ret, int size);
    void		unlock(Stream* stream, void* buffer, int size, long dts);
  };
}

#endif // _OUTPUTSTREAM_H
