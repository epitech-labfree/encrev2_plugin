#ifndef _INPUTSTREAM_H
# define _INPUTSTREAM_H

#include "VlcStream.hh"
#include "Imem.hh"
#include "vlc_system_strategy.hh"
#include <boost/signals2.hpp>

namespace encre
{
  typedef boost::signals2::signal<unsigned int (const char *, unsigned int)> t_bsign;

  class	InputVlcStream : public VlcStream
  {
  private :
    Imem		m_imem;
    t_bsign		m_signal;
    FB::PluginWindow*	m_window;

  public :
    InputVlcStream(Encre<libvlc_instance_t>*);
    t_bsign&		on_data_needed();
    int			getVideo(void* data, const char* cookie, int64_t* dts, int64_t* pts, unsigned* flags, size_t* len, void** buffer);
    int			release(void *data, const char *cookie, size_t, void *buffer);
    bool		start();
  };
}

#endif // _INPUTSTREAM_H
