#include "Imem.hh"

int
Vlc::getVideo(void* data, const char* cookie, int64_t* dts, int64_t* pts,
			     unsigned* flags, size_t* len, void** buffer)
{
  Vlc	*myVlc = static_cast<Vlc*>(data);
  if (myVlc == 0)
    return -1;
  *buffer = new char [4096];
  *len = myVlc->_net->read(*buffer, 4096);
  return (*len ? 0 : -1);
}

int
Vlc::release(void *data, const char *cookie, size_t, void *buffer)
{
  delete (char*)buffer;
  buffer = NULL;
  return 0;
}

void
Vlc::setVideoGetCallback(void* callback)
{
  char    param[64];

  sprintf(param, ":imem-get=%"PRId64, (long long int)callback);
  addRuntimeOption(param);
}

void
Vlc::setVideoReleaseCallback(void* callback)
{
  char    param[64];

  sprintf(param, ":imem-release=%"PRId64, (long long int)callback);
  addRuntimeOption(param);
}

void
Vlc::setImemDataCtx( void* dataCtx )
{
  char    param[64];
  sprintf(param, ":imem-data=%"PRId64, (long long int)dataCtx);
  addRuntimeOption(param);
}
