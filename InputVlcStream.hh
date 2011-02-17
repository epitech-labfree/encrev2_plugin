#ifndef _INPUTSTREAM_H
# define _INPUTSTREAM_H

#include "VlcStream.hh"
#include "Imem.hh"
#include <boost/signals2.hpp>

namespace encre
{
  typedef boost::signals2::signal<unsigned int (const char *, unsigned int)> t_bsign;

  class	InputStream : public VlcStream
  {
  private :
    Imem		m_imem;
    t_bsign		m_signal;

  public :
    InputStream();
    t_bsign&		on_data_needed();
    int			getVideo(void* data, const char* cookie, int64_t* dts, int64_t* pts, unsigned* flags, size_t* len, void** buffer);
    int			release(void *data, const char *cookie, size_t, void *buffer);
  };
}

#endif // _INPUTSTREAM_H
