#include "InputVlcStream.hh"
#include <iostream>

namespace encre
{
  InputVlcStream::InputVlcStream(Encre<libvlc_instance_t>* encre) : VlcStream(encre), m_window(0)
  {
    m_media = libvlc_media_new_location(m_encre->getData(), "imem://width=400:height=400:fps=30:cookie=0:codec=H264:cat=4:caching=0:demux=ts:text-renderer dummy");
    displayData();
  }

  t_bsign&
  InputVlcStream::on_data_needed()
  {
  }

  int
  InputVlcStream::getVideo(void* data, const char* cookie, int64_t* dts, int64_t* pts,
		 unsigned* flags, size_t* len, void** buffer)
  {
    // Vlc	*myVlc = static_cast<Vlc*>(data);
    // if (myVlc == 0)
    //   return -1;
    // *buffer = new char [4096];
    // *len = myVlc->_net->read(*buffer, 4096);
    //use the callback of the InputVlcStream
    std::cout << "lol" << std::endl;
    *len = 0;
    return (*len ? 0 : -1);
  }

  int
  InputVlcStream::release(void *data, const char *cookie, size_t, void *buffer)
  {
    std::cout << "relol" << std::endl;
    delete (char*)buffer;
    buffer = NULL;
    return 0;
  }

  bool
  InputVlcStream::displayData()
  {
    if (m_media = 0)
      return (false);
    m_mp = libvlc_media_player_new(m_encre->getData());
    
    m_imem.setVideoGetCallback(this, reinterpret_cast<void*>(&encre::InputVlcStream::getVideo));
    m_imem.setVideoReleaseCallback(this, reinterpret_cast<void*>(&encre::InputVlcStream::release));
    m_imem.setImemDataCtx(this, this);

    libvlc_media_player_set_media(m_mp, m_media);
    VlcSystemStrategy::set_window(m_mp, m_window);
    play();
    return true;
  }
}
