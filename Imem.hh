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
  void		setVideoGetCallback(Stream* stream, void* callback);
  void		setVideoReleaseCallback(Stream* stream, void* callback);
  void		setImemDataCtx(Stream* stream, void* dataCtx);
  void		setImem(Stream* stream, const std::string&, void* dataCtx);
};

}

#endif // _IMEM_H
