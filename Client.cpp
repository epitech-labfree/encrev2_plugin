#include <iostream>
#include <vector>
#include <boost/signals2.hpp>
#include "Protocol.hh"
#include "Client.hh"

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
