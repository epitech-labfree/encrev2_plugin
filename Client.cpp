#include <iostream>
#include <vector>
#include <boost/signals2.hpp>
#include "Protocol.hh"
#include "Client.hh"

void
Client::get_data(char** data, size_t* size) {
	// XXX: Check for brain dead people who don't call is_data_received
 	for (unsigned int i = 0; i < m_buff->size(); ++i) {
		*data[i] = m_buff->at(i);
	}
	*size = m_buff->size();
	delete m_buff;
}
