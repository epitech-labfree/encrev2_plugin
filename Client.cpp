#include <iostream>
#include <vector>
#include <boost/signals2.hpp>
#include "Protocol.hh"
#include "Client.hh"

inline Client::state&
Client::get_state() {
	return m_state;
}

inline void
Client::send_data(char* buf, size_t size) const {
	m_network->write(std::string(buf, size));
}

inline void
Client::receive_data(std::vector<unsigned char>* buff) {
	if (m_buff != 0)
		std::cerr << "Client::receive_data: Memory Leak" << std::endl;
	m_buff = new std::vector<unsigned char>(*buff);
	delete buff;
}

inline bool
Client::is_data_received() const {
	return m_buff != 0;
}

void
Client::get_data(char** data, size_t* size) {
 	for (unsigned int i = 0; i < m_buff->size(); ++i) {
		*data[i] = m_buff->at(i);
	}
	*size = m_buff->size();
	delete m_buff;
}
