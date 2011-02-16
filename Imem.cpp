#include "Imem.hh"

namespace vlc
{

int
Imem::getVideo(void* data, const char* cookie, int64_t* dts, int64_t* pts,
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
Imem::release(void *data, const char *cookie, size_t, void *buffer)
{
  delete (char*)buffer;
  buffer = NULL;
  return 0;
}

void
Imem::setVideoGetCallback(Stream* stream, void* callback)
{
  std::ostringstream oss;

  oss << ":imem-get=" << reinterpret_cast<long long int>(callback);
  stream->setOptions(oss.str().c_str());
}

void
Imem::setVideoReleaseCallback(Stream* stream, void* callback)
{
  std::ostringstream oss;

  oss << ":imem-release=" << reinterpret_cast<long long int>(callback);
  stream->setOptions(oss.str().c_str());
}

void
Imem::setImemDataCtx(Stream* stream, void* dataCtx)
{
  std::ostringstream oss;

  oss << ":imem-data=" << reinterpret_cast<long long int>(callback);
  stream->setOptions(oss.str().c_str());
}

}
