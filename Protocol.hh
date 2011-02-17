#ifndef ENCREV2_PLUGIN_PROTOCOL_HH
#define ENCREV2_PLUGIN_PROTOCOL_HH
#include <string>

class binary_data;
class Client;

class Protocol {
public:
	Protocol() {}
	~Protocol() {}
	bool parse_incoming_data(binary_data&, Client&);

private:
	bool is_header_complete() const;
};

#endif
