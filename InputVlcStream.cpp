#include "InputVlcStream.hh"
#include <iostream>

namespace encre
{
  InputVlcStream::InputVlcStream(Encre<libvlc_instance_t>* encre) : VlcStream(encre), m_window(0)
  {
    m_media = libvlc_media_new_location(m_encre->getData(), "imem://width=400:height=400:fps=30:cookie=0:codec=H264:cat=4:caching=0");
  }

  t_bsign&
  InputVlcStream::on_data_needed()
  {
  }

  bool
  InputVlcStream::start()
  {
    if (m_media == 0)
      return (false);
    m_mp = libvlc_media_player_new_from_media(m_media);

    m_imem.setVideoGetCallback(this, reinterpret_cast<void*>(&encre::InputVlcStream::getVideo));
    m_imem.setVideoReleaseCallback(this, reinterpret_cast<void*>(&encre::InputVlcStream::release));
    m_imem.setImemDataCtx(this, this);
    setOptions("");

    VlcSystemStrategy::set_window(m_mp, m_window);
    m_client->control();
    play();
    return true;
  }

  int
  InputVlcStream::getVideo(void* data, const char* cookie, int64_t* dts, int64_t* pts, unsigned* flags, size_t* len, void** buffer)
  {
    InputVlcStream*	myInput = static_cast<InputVlcStream*>(data);

    if (myInput == 0)
      return -1;
    if (myInput->m_client->is_data_received())
      {
	std::cout << "111111111111111111111111111woops1" << std::endl;
	*len = 4096;
	*buffer = new char [*len];
	myInput->m_client->get_data((char**)buffer, len);
      }
    else
      {
	//std::cout << "222222222222222222222222222woops2" << std::endl;
	*buffer = 0;
	*len = 0;
	return 0;
      }
    return (*len ? 0 : -1);
  }

  int
  InputVlcStream::release(void *data, const char *cookie, size_t, void *buffer)
  {
    delete (char*)buffer;
    buffer = NULL;
    return 0;
  }
}
