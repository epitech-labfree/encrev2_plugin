#include "OutputVlcStream.hh"
#include "vlc_system_strategy.hh"
#include <iostream>

namespace encre
{
  OutputVlcStream::OutputVlcStream(Encre<libvlc_instance_t>* encre) : VlcStream(encre), m_videoSource(""), m_soundSource("")
  {
    std::string media;    
    if (!getSource() || (m_videoSource == "" && m_soundSource == ""))
      throw "exception to catch in the instance of encre";
    if (m_videoSource != "" && m_soundSource == "")
      media = m_videoSource;
    else if (m_videoSource == "" && m_soundSource != "")
      media = m_soundSource;
    else //TODO : I don't know how to treat this case
      {
	media = m_videoSource;
	//media += ":input-slave=";
	//media += m_soundSource;
      }
    m_media = libvlc_media_new_location(m_encre->getData(), media.c_str());
    setOptions(m_soundSource);
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
    libvlc_media_player_set_media(m_mp, m_media);
    setOptions("");
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
    //it's here where we can send the data of the stream
    // XXX: Check if size > UINT_MAX //osef
    char* copy = new char[size]; // Change this to a smartpointer
    memcpy(copy, buffer, size);
    stream->m_client->send_data(copy, size);
  }

  bool
  OutputVlcStream::getSource()
  {
    if (!VlcSystemStrategy::get_webcam_mrl(m_videoSource))
      return (false);
    if (!VlcSystemStrategy::get_sound_mrl(m_soundSource))
      return (false);
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
