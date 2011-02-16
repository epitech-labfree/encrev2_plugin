#include "Smem.hh"
void
Smem::lock(Vlc* vlc, void** pp_ret,
	   int size)
{
  int * buffer = new int[size];
  *pp_ret = (void*)buffer;
}

void
Smem::unlock( Vlc* vlc, void* buffer,
	     int size,
	     long dts )
{
  // c'est ici que l'on traite la video
  if (vlc && vlc->_net->isConnected())
    {
      //Network* net = Network::getInstance();
      vlc->_net->write(buffer, size);
      delete (char*)buffer;
    }
}

void
Smem::setVideoLockCallback(void* callback)
{
  char    param[64];

  sprintf(param, ":sout-smem-video-prerender-callback=%"PRId64, (long long int)callback);
  addRuntimeOption(param);
}

void
Smem::setVideoUnlockCallback(void* callback)
{
  char    param[64];

  sprintf(param, ":sout-smem-video-postrender-callback=%"PRId64, (long long int)callback);
  addRuntimeOption(param);
}

void
Smem::setDataLockCallback(void* callback)
{
  char    param[64];

  sprintf(param, ":sout-smem-data-prerender-callback=%"PRId64, (long long int)callback);
  addRuntimeOption(param);
}

void
Smem::setDataUnlockCallback(void* callback)
{
  char    param[64];

  sprintf(param, ":sout-smem-data-postrender-callback=%"PRId64, (long long int)callback);
  addRuntimeOption(param);
}

void
Smem::setAudioLockCallback(void* callback)
{
  char    param[64];

  sprintf(param, ":sout-smem-audio-prerender-callback=%"PRId64, (long long int)callback);
  addRuntimeOption(param);
}

void
Smem::setAudioUnlockCallback(void* callback)
{
  char    param[64];

  sprintf(param, ":sout-smem-audio-postrender-callback=%"PRId64, (long long int)callback);
  addRuntimeOption(param);
}


void
Smem::setVideoDataCtx( void* dataCtx )
{
  char    param[64];

  sprintf( param, ":sout-smem-video-data=%"PRId64, (long long int)dataCtx );
  addRuntimeOption( param );
}

void
Smem::setDataCtx( void* dataCtx )
{
  char    param[64];

  sprintf(param, ":sout-smem-data-data=%"PRId64, (long long int)dataCtx);
  addRuntimeOption(param);
}
