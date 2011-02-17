#ifndef _INPUTSTREAM_H
# define _INPUTSTREAM_H

#include "Stream.hh"
#include "Imem.hh"
#include <boost/signals2.hpp>

namespace encre
{
  typedef boost::signals2::signal<unsigned int (const char *, unsigned int)> t_bsign;

  class	InputStream : public Stream
  {
  private :
    Imem		m_imem;
    t_bsign		m_signal;

  public :
    t_bsign&		on_data_needed();
    InputStream();
  };
}

#endif // _INPUTSTREAM_H
