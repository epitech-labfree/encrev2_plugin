#include "InputVlcStream.hh"

namespace encre
{
  InputStream::InputStream()
  {
  }

  t_bsign&
  InputStream::on_data_needed()
  {
  }

  int
  InputStream::getVideo(void* data, const char* cookie, int64_t* dts, int64_t* pts,
		 unsigned* flags, size_t* len, void** buffer)
  {
    // Vlc	*myVlc = static_cast<Vlc*>(data);
    // if (myVlc == 0)
    //   return -1;
    // *buffer = new char [4096];
    // *len = myVlc->_net->read(*buffer, 4096);
    //use the callback of the InputStream
    *len = 0;
    return (*len ? 0 : -1);
  }

  int
  InputStream::release(void *data, const char *cookie, size_t, void *buffer)
  {
    delete (char*)buffer;
    buffer = NULL;
    return 0;
  }

}
