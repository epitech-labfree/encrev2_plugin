
namespace vlc
{

class Imem
{
public :
  int		getVideo(void* data, const char* cookie, int64_t* dts, int64_t* pts,
			 unsigned* flags, size_t* len, void** buffer);
  int		release(void *data, const char *cookie, size_t, void *buffer);
  void		setVideoGetCallback(void* callback);
  void		setVideoReleaseCallback(void* callback);
  void		setImemDataCtx(void* dataCtx);
};

}
