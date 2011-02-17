#include "Smem.hh"

//Allow PRId64 to be defined:
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

#include <sstream>

namespace encre
{

void
Smem::setVideoLockCallback(Stream* stream, void* callback)
{
  setSmem(stream, "video", "prerender-callback", callback);
}

void
Smem::setVideoUnlockCallback(Stream* stream, void* callback)
{
  setSmem(stream, "video", "postrender-callback", callback);
}

void
Smem::setDataLockCallback(Stream* stream, void* callback)
{
  setSmem(stream, "data", "prerender-callback", callback);
}

void
Smem::setDataUnlockCallback(Stream* stream, void* callback)
{
  setSmem(stream, "data", "postrender-callback", callback);
}

void
Smem::setAudioLockCallback(Stream* stream, void* callback)
{
  setSmem(stream, "audio", "prerender-callback", callback);
}

void
Smem::setAudioUnlockCallback(Stream* stream, void* callback)
{
  setSmem(stream, "audio", "postrender-callback", callback);
}

void
Smem::setVideoDataCtx(Stream* stream, void* dataCtx)
{
  setSmem(stream, "video", "data", dataCtx);
}

void
Smem::setDataCtx(Stream* stream, void* dataCtx)
{
  setSmem(stream, "data", "data", dataCtx);
}

void
Smem::setSmem(Stream* stream, const std::string& which, const std::string& why, void* data)
{
  std::ostringstream oss;

  oss << ":sout-smem-" << which << "-" << why << "=" << reinterpret_cast<long long int>(data);
  stream->setOptions(oss.str().c_str());
}

}
