#include "Protocol.hh"
#include "Client.hh"
#include <string>

bool
Protocol::parse_incoming_data(binary_data& buf, Client& client) {

}

bool
Protocol::is_header_complete() const {
	
}

// TODO: foo will be a boolean parser who return true if the buffer is a valid
// PUT message
bool
Protocol::foo() const {
	return true;
}
