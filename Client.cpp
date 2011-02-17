#include "Protocol.hh"
#include "Network.hh"
#include "Client.hh"
#include <boost/signals2.hpp>

Client::state&
Client::get_state() {
	return m_state;
}

boost::signals2::signal<void (char**, size_t*)>&
Client::get_sig() {
	return m_sig;
}

void
Client::control(char** buf, size_t* size) {
	m_sig(buf, size);
}
