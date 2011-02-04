#include "protocol.hh"
#include <string>

const char*
Protocol::put(const std::string& stream) {
  std::string* str = new std::string("PUT ");
	str->append(stream);
	str->append("\n\n");
	return str->c_str();
}

const char*
Protocol::get(const std::string& stream) {
	std::string* str = new std::string("GET ");
	str->append(stream);
	str->append("\n\n");
	return str->c_str();
}
