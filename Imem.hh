#ifndef _IMEM_H
# define _IMEM_H

//Allow PRId64 to be defined:
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <cstdio>

#include "Stream.hh"

namespace encre
{

class Imem
{
public :
  int		getVideo(void* data, const char* cookie, int64_t* dts, int64_t* pts,
			 unsigned* flags, size_t* len, void** buffer);
  int		release(void *data, const char *cookie, size_t, void *buffer);
  void		setVideoGetCallback(Stream* stream, void* callback);
  void		setVideoReleaseCallback(Stream* stream, void* callback);
  void		setImemDataCtx(Stream* stream, void* dataCtx);
};

}

#endif // _IMEM_H
