#include "Stream.hh"

namespace	encre
{
  Stream::~Stream()
  {
  }

  Stream::e_state			Stream::state()
  {
    return (m_state);
  }

  Stream::Stream(Encre<libvlc_instance_t>* lol) : m_encre(lol), m_state(INACTIVE), m_client(new Client("localhost", 4242))
  {
  }
}
