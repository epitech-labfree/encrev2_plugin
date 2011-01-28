#include "protocol.hh"
#include <string>

const char*
Protocol::put(const char* stream) {
	std::string str("PUT ");
	str.append(stream);
	str.append("\n\n");
	return str.c_str();
}

const char*
Protocol::get(const char* stream) {
	std::string str("GET ");
	str.append(stream);
	str.append("\n\n");
	return str.c_str();
}

