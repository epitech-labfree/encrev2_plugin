// should contain smem dirty details.

#include <boost/utility.hpp>
#include "Stream.hh"

namespace vlc
{
  class Smem : boost::noncopyable
  {
  public :
    void		lock(Stream* stream, void** pp_ret, int size);
    void		unlock(Stream* stream, void* buffer, int size, long dts );
    void		setVideoLockCallback(Stream* stream, void* callback);
    void		setVideoUnlockCallback(Stream* stream, void* callback);
    void		setDataLockCallback(Stream* stream, void* callback);
    void		setDataUnlockCallback(Stream* stream, void* callback);
    void		setAudioLockCallback(Stream* stream, void* callback);
    void		setAudioUnlockCallback(Stream* stream, void* callback);
    void		setVideoDataCtx(Stream* stream, void* dataCtx);
    void		setDataCtx(Stream* stream, void* dataCtx);
  };
}
