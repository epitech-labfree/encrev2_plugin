#include "OutputVlcStream.hh"
#include "vlc_system_strategy.hh"
#include <iostream>

namespace encre
{
  OutputVlcStream::OutputVlcStream(Encre<libvlc_instance_t>* encre) : VlcStream(encre), m_videoSource(""), m_soundSource("")
  {
    
    if (!getSource() || (m_videoSource == "" && m_soundSource == ""))
      throw "exception to catch in the instance of encre";
    if (m_videoSource != "" && m_soundSource == "")
      m_media = libvlc_media_new_location(m_encre->getData(), m_videoSource.c_str());
    else if (m_videoSource == "" && m_soundSource != "")
      m_media = libvlc_media_new_location(m_encre->getData(), m_soundSource.c_str());
    else //TODO : I don't know how to treat this case
      m_media = libvlc_media_new_location(m_encre->getData(), m_videoSource.c_str());
  }

  t_bsign&
  OutputVlcStream::on_data_available()
  {
  }

  bool
  OutputVlcStream::start()
  {
    if (!m_media)
      {
	std::clog << "vlc media is not set" << std::endl;
	return false;
      }
    m_smem.setDataLockCallback(this, reinterpret_cast<void*>(&encre::OutputVlcStream::lock));
    m_smem.setDataUnlockCallback(this, reinterpret_cast<void*>(&encre::OutputVlcStream::unlock));
    m_smem.setDataCtx(this, this);
    m_mp = libvlc_media_player_new(m_encre->getData());
    if (m_mp == 0)
      {
	std::clog << "libvlc_media_player_new: failed to create the media player" << std::endl;
	return false;
      }
    std::cout << "aie aie aie" << std::endl;

    libvlc_media_player_set_media(m_mp, m_media);
    setOptions("");
    std::cout << "aie aie aie" << std::endl;
    VlcSystemStrategy::set_window(m_mp, 0);
    play();
    return true;
  }

  void
  OutputVlcStream::lock(Stream* stream, void** pp_ret, int size)
  {
    int* buffer = new int[size];
    *pp_ret = (void*)buffer;
  }

  void
  OutputVlcStream::unlock(Stream* stream, void* buffer, int size, long dts)
  {
    std::cout << "i'm hereeeeeeeeee" << std::endl;
    //it's here where we can send the data of the stream
    // XXX: Check if size > UINT_MAX //osef
    stream->m_client->send_data((char*)buffer, size);
    delete (char*)buffer;
  }

  bool
  OutputVlcStream::getSource()
  {
    if (!VlcSystemStrategy::get_webcam_mrl(m_videoSource))
      return (false);
    // TODO : sound
    return (true);
  }

  bool
  OutputVlcStream::setSource(const std::string& video, const std::string& sound)
  {
    if (video != "")
      m_videoSource = video;
    if (sound != "")
      m_soundSource = sound;
  }
}
