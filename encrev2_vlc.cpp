#include "encrev2_vlc.hh"

const char*	vlc::Vlc::DefaultArgs[] =
  {
    "-I",
    "--ignore-config",
    "dummy",
    "-vv"
  };

namespace vlc
{
  Vlc::Vlc() :m_vlc(0), m_stream(0)
  {
    m_vlc = libvlc_new(sizeof(DefaultArgs) / sizeof(*DefaultArgs), DefaultArgs);
  }

  Vlc::Vlc(const std::vector<std::string>& vlcOpts) :m_vlc(0), m_stream(0)
  {
    const char*	vlcArgs[vlcOpts.size()];
    for (unsigned int i=0; i < vlcOpts.size(); ++i)
      {
	vlcArgs[i] = vlcOpts[i].c_str();
      }
    m_vlc = libvlc_new(sizeof(DefaultArgs) / sizeof(*DefaultArgs), vlcArgs);
  }

  Stream*			Vlc::getStream() const
  {
    return m_stream;
  }
}
