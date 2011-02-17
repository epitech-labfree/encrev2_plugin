#include "Imem.hh"

#include <sstream>

namespace encre
{

  void
  Imem::setVideoGetCallback(Stream* stream, void* callback)
  {
    setImem(stream, "get", callback);
  }

  void
  Imem::setVideoReleaseCallback(Stream* stream, void* callback)
  {
    setImem(stream, "release", callback);
  }

  void
  Imem::setImemDataCtx(Stream* stream, void* dataCtx)
  {
    setImem(stream, "data", dataCtx);
  }

  void
  Imem::setImem(Stream* stream, const std::string& which, void* data)
  {
    std::ostringstream oss;

    oss << ":imem-" << which << "=" << reinterpret_cast<long long int>(data);
    stream->setOptions(oss.str().c_str());
  }

}
