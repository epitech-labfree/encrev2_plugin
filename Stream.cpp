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

  Stream::Stream() : m_state(INACTIVE)
  {
  }
}
