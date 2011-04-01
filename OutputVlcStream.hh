#ifndef _OUTPUTSTREAM_H
# define _OUTPUTSTREAM_H

#include "VlcStream.hh"
#include "Smem.hh"

namespace encre
{

  class	OutputVlcStream : public VlcStream
  {
  private :
    Smem		m_smem;
    std::string		m_videoSource;
    std::string		m_soundSource;

  public :
    OutputVlcStream(Encre<libvlc_instance_t>*);

    static void		lock(Stream* stream, void** pp_ret, int size);
    static void		unlock(Stream* stream, void* buffer, int size, long dts);
    bool		getSource();
    bool		setSource(const std::string&, const std::string&);
    bool		start();
  };
}

#endif // _OUTPUTSTREAM_H
