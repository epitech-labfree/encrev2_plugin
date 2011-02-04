#ifndef ENCREV2_PLUGIN_PROTOCOL_HH
#define ENCREV2_PLUGIN_PROTOCOL_HH
#include <string>

class Protocol {
	public:
	static const char* put(const std::string&);
	static const char* get(const std::string&);

	private:
	Protocol& operator=(const Protocol&);
	Protocol(const Protocol&);
};

#endif
