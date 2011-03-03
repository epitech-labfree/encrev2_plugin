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

  Stream::Stream(Encre<libvlc_instance_t>* lol) : m_encre(lol), m_state(INACTIVE), m_client(new Client("127.0.0.1", "4242"))
  {
  }
}
