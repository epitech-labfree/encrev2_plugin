#include "OutputVlcStream.hh"
#include "vlc_system_strategy.hh"
#include <iostream>

namespace encre
{
  t_bsign&
  OutputStream::on_data_available()
  {
  }

  OutputStream::OutputStream() : m_videoSource(""), m_soundSource("")
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

  bool
  OutputStream::stream()
  {
    if (!m_media)
      {
	std::clog << "vlc media is not set" << std::endl;
	return false;
      }
    m_smem.setDataLockCallback(this, reinterpret_cast<void*>(&encre::OutputStream::lock));
    m_smem.setDataUnlockCallback(this, reinterpret_cast<void*>(&encre::OutputStream::unlock));
    m_smem.setDataCtx(this, this);
    m_mp = libvlc_media_player_new(m_encre->getData());
    if (m_mp == 0)
      {
	std::clog << "libvlc_media_player_new: failed to create the media player" << std::endl;
	return false;
      }
    libvlc_media_player_set_media(m_mp, m_media);
    return true;
  }

  void
  OutputStream::lock(Stream* stream, void** pp_ret, int size)
  {
    int* buffer = new int[size];
    *pp_ret = (void*)buffer;
  }

  void
  OutputStream::unlock(Stream* stream, void* buffer, int size, long dts)
  {
    //it's here where we can send the data of the stream
    // if (stream && stream->_net->isConnected())
    //   {
    //     vlc->_net->write(buffer, size);
    delete (char*)buffer;
    //   }
  }

  bool
  OutputStream::getSource()
  {
    if (!VlcSystemStrategy::get_webcam_mrl(m_videoSource))
      return (false);
    // TODO : sound
    return (true);
  }

  void
  OutputStream::setSource(const std::string& video, const std::string& sound)
  {
    if (video != "")
      m_videoSource = video;
    if (sound != "")
      m_soundSource = sound;
  }

}
