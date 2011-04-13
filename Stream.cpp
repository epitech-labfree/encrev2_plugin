#include "Stream.hh"

namespace	encre
{
  Stream::~Stream()
  {
	  delete m_client;
	  m_client = 0;
  }

  Stream::e_state			Stream::state()
  {
    return (m_state);
  }

  Stream::Stream(Encre<libvlc_instance_t>* instance) : m_encre(instance),
  	m_state(INACTIVE),
	m_client(new Client(*(instance->m_host), instance->m_port))
  {
  }
}
