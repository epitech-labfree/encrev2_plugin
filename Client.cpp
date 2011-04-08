#include <iostream>
#include <vector>
#include <boost/signals2.hpp>
#include "Protocol.hh"
#include "Client.hh"

Client::Client(const std::string& host, short int port)
	: m_network(new Network<Client>(host, port)),
	m_protocol(new Protocol()), m_state(NOT_CONNECTED), m_buffers()
{
	switch (m_network->get_state()) {
		case Network<Client>::CONNECTED:
			m_state = CONNECTED;
			std::clog << "NOTE: Client: state = CONNECTED " << std::endl;
			break;
		case Network<Client>::NOT_CONNECTED:
			m_state = NOT_CONNECTED;
			std::clog << "NOTE: Client: state = NOT_CONNECTED" << std::endl;
			break;
		case Network<Client>::ERROR:
		default:
			m_state = ERROR;
			std::clog << "NOTE: Client: state = ERROR" << std::endl;
	}
	std::clog << "DEBUG: Client: created" << std::endl;
	m_network->set_receiver(this);
}

// Do *NOT* call whitout call is_data_received first.
void
Client::get_data(char** data, size_t* size) {
	encre::buffer_ptr p = m_buffers.front();
	m_buffers.pop_front();
	encre::buffer* b = p.get();

 	for (unsigned int i = 0; i < b->size(); ++i) {
		(*data)[i] = b->at(i);
	}

	*size = b->size();
}

void
Client::send_data(char* buf, size_t size) {
	if (m_state == CONNECTED && m_protocol->foo()) { //TODO: Replace foo() by a parser
		m_state = PUBLISHING;
		m_network->write("PUT toto\n\n", 10); //XXX: CRAP
		std::clog << "NOTE: Client: state = PUBLISHING" << std::endl;
		goto write;
	}
	else if (m_state == PUBLISHING) {
		goto write;
	}
	else {
		return ;
	}
write:
	m_network->write(buf, size);
}
