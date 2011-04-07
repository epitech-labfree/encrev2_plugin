#include "encre.hh"
#include "VlcStream.hh"
#include "OutputVlcStream.hh"
#include "InputVlcStream.hh"
#include "vlc_system_strategy.hh"

#include <iostream>

static const char * vlc_args[] = {
  "-I", "dummy", /* Don't use any interface */
  "--ignore-config", /* Don't use VLC's config */
  ""
};

namespace encre
{
  template <typename T>
  Encre<T>::Encre() : m_data(0), m_stream(0)
  {
    std::clog << "Unknown type" << std::endl;
  }

  template <>
  Encre<libvlc_instance_t>::Encre() : m_data(0), m_stream(0)
  {
    std::cout << "Encre Initialisation:" << (unsigned int)this << std::endl;
    m_data = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);
  }

  template <typename T>
  Encre<T>::Encre(const std::vector<std::string>& vlcOpts) : m_data(0), m_stream(0)
  {
    std::clog << "Unknown type" << std::endl;
  }

  template <>
  Encre<libvlc_instance_t>::Encre(const std::vector<std::string>& vlcOpts) : m_data(0), m_stream(0)
  {
    std::cout << "Encre Initialisation2:" << (unsigned int)this << std::endl;
    const char*	vlcArgs[vlcOpts.size()];
    for (unsigned int i=0; i < vlcOpts.size(); ++i)
      {
	vlcArgs[i] = vlcOpts[i].c_str();
      }
    m_data = libvlc_new(sizeof(vlcArgs) / sizeof(*vlcArgs), vlcArgs);
  }

  template <typename T>
  Encre<T>::~Encre()
  {
	delete m_data;	  
	m_data = 0;
  }

 template <typename T>
  Stream*	Encre<T>::getStream(e_action todo)
  {
    return m_stream;
  }

  template <>
  Stream*	Encre<libvlc_instance_t>::getStream(e_action todo)
  {
    if (todo != NOTHING && m_stream == 0)
      {
	if (m_stream)
	  {
	    m_stream = 0;
	    delete m_stream;
	  }
	switch (todo)
	  {
	  case STREAM :
	    m_stream = new OutputVlcStream(this);
	    break;
	  case DISPLAY :
	    m_stream = new InputVlcStream(this);
	    break;
	  default :
	    m_stream = 0;
	    break;
	  }
      }
    return m_stream;
  }

  template <typename T>
  bool			Encre<T>::start()
  {
    return true;
  }

  template <>
  bool			Encre<libvlc_instance_t>::start()
  {
    std::cout << "here we initilise the network, return depend of it" << std::endl;
    return true;
  }

  template <typename T>
  T*			Encre<T>::getData()
  {
    return (m_data);
  }

  template <>
  libvlc_instance_t*	Encre<libvlc_instance_t>::getData()
  {
    return (m_data);
  }

  template <typename T> void
  Encre<T>::set_window(FB::PluginWindow *w)
  {
	m_window = w; 
  }
}
