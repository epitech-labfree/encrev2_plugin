#include "OutputStream.hh"

namespace encre
{
  t_bsign&
  OutputStream::on_data_available()
  {
    
  }

  OutputStream::OutputStream()
  {
  }

  void
  OutputStream::lock(Stream* stream, void** pp_ret, int size)
  {
    int* buffer = new int[size];
    *pp_ret = (void*)buffer;
  }

  void
  OutputStream::unlock(Stream* stream, void* buffer, int size, long dts)
  {
    //it's here where we can send the data of the stream
    // if (stream && stream->_net->isConnected())
    //   {
    //     vlc->_net->write(buffer, size);
    //     delete (char*)buffer;
    //   }
  }

}
