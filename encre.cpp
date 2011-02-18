#include "encre.hh"
#include "VlcStream.hh"
#include "OutputVlcStream.hh"
#include "InputVlcStream.hh"

#include <iostream>

template <typename T>
const char*	encre::Encre<T>::DefaultArgs[] =
  {
    "-I",
    "--ignore-config",
    "dummy",
    "-vv"
  };

namespace encre
{
  template <typename T>
  Encre<T>::Encre() : m_data(0), m_stream(0)
  {
    std::clog << "Unknown ype" << std::endl;
  }

  template<>
  Encre<libvlc_instance_t>::Encre() : m_data(0), m_stream(0)
  {
    m_data = libvlc_new(sizeof(DefaultArgs) / sizeof(*DefaultArgs), DefaultArgs);
  }

  template <typename T>
  Encre<T>::Encre(const std::vector<std::string>& vlcOpts) :m_data(0), m_stream(0)
  {
    std::clog << "Unknown type" << std::endl;
  }

  template <>
  Encre<libvlc_instance_t>::Encre(const std::vector<std::string>& vlcOpts) :m_data(0), m_stream(0)
  {
    const char*	vlcArgs[vlcOpts.size()];
    for (unsigned int i=0; i < vlcOpts.size(); ++i)
      {
	vlcArgs[i] = vlcOpts[i].c_str();
      }
    m_data = libvlc_new(sizeof(vlcArgs) / sizeof(*vlcArgs), vlcArgs);
  }

  template <typename T>
  Stream*	Encre<T>::getStream(e_action todo)
  {
    return m_stream;
  }
  template <>
  Stream*	Encre<libvlc_instance_t>::getStream(e_action todo)
  {
    if (todo != NOTHING)
      {
	if (m_stream)
	  ;
	switch (todo)
	  {
	  case STREAM :
	    std::cout << STREAM << "   stream=" << todo << std::endl;
	    m_stream = new OutputStream;
	    std::cout << STREAM << "   stream=" << todo << std::endl;
	    break;
	  case DISPLAY :
	    m_stream = new InputStream();
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
    std::cout << "here we initilise the network, return depend on it" << std::endl;
    return true;
  }

  template <typename T>
  T*			Encre<T>::getData() const
  {
    return (m_data);
  }

  template <>
  libvlc_instance_t*	Encre<libvlc_instance_t>::getData() const
  {
    return (m_data);
  }

}
