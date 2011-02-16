#include "Smem.hh"

//Allow PRId64 to be defined:
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

#include <sstream>

namespace vlc
{
void
Smem::lock(Stream* stream, void** pp_ret, int size)
{
  int * buffer = new int[size];
  *pp_ret = (void*)buffer;
}

void
Smem::unlock(Stream* stream, void* buffer, int size, long dts)
{
  //it's here where we can send the data of the stream
  // if (stream && stream->_net->isConnected())
  //   {
  //     vlc->_net->write(buffer, size);
  //     delete (char*)buffer;
  //   }
}

void
Smem::setVideoLockCallback(Stream* stream, void* callback)
{
  std::ostringstream oss;

  oss << ":sout-smem-video-prerender-callback=" << reinterpret_cast<long long int>(callback);
  stream->setOptions(oss.str().c_str());
}

void
Smem::setVideoUnlockCallback(Stream* stream, void* callback)
{
  std::ostringstream oss;

  oss << ":sout-smem-video-postrender-callback=" << reinterpret_cast<long long int>(callback);
  stream->setOptions(oss.str().c_str());
}

void
Smem::setDataLockCallback(Stream* stream, void* callback)
{
  std::ostringstream oss;

  oss << ":sout-smem-data-prerender-callback=" << reinterpret_cast<long long int>(callback);
  stream->setOptions(oss.str().c_str());
}

void
Smem::setDataUnlockCallback(Stream* stream, void* callback)
{
  std::ostringstream oss;

  oss << ":sout-smem-data-postrender-callback=" << reinterpret_cast<long long int>(callback);
  stream->setOptions(oss.str().c_str());
}

void
Smem::setAudioLockCallback(Stream* stream, void* callback)
{
  std::ostringstream oss;

  oss << ":sout-smem-audio-prerender-callback=" << reinterpret_cast<long long int>(callback);
  stream->setOptions(oss.str().c_str());
}

void
Smem::setAudioUnlockCallback(Stream* stream, void* callback)
{
  std::ostringstream oss;

  oss << ":sout-smem-audio-postrender-callback=" << reinterpret_cast<long long int>(callback);
  stream->setOptions(oss.str().c_str());
}


void
Smem::setVideoDataCtx(Stream* stream, void* dataCtx)
{
  std::ostringstream oss;

  oss << ":sout-smem-video-data=" << reinterpret_cast<long long int>(dataCtx);
  stream->setOptions(oss.str().c_str());
}

void
Smem::setDataCtx(Stream* stream, void* dataCtx)
{
  std::ostringstream oss;

  oss << ":sout-smem-data-data=" << reinterpret_cast<long long int>(dataCtx);
  stream->setOptions(oss.str().c_str());
}

}
