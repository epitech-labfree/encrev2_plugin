// should contain smem dirty details.

class Smem : boost::noncopyable
{
public :
  void		lock(Vlc* vlc, void** pp_ret, int size);
  void		unlock( Vlc* vlc, void* buffer, int size, long dts );
  void		setVideoLockCallback(void* callback);
  void		setVideoUnlockCallback(void* callback);
  void		setDataLockCallback(void* callback);
  void		setDataUnlockCallback(void* callback);
  void		setAudioLockCallback(void* callback);
  void		setAudioUnlockCallback(void* callback);
  void		setVideoDataCtx(void* dataCtx);
  void		setDataCtx(void* dataCtx);
protected :
  Smem();
};
