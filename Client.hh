class Protocol;
class Network;

# include <boost/signals2.hpp>

#ifndef ENCREV2_PLUGIN_CLIENT_HH
# define ENCREV2_PLUGIN_CLIENT_HH

struct binary_data {
	char* data;
	size_t size;
};

class Client {
public:
	enum state {
		ERROR,
		NOT_CONNECTED,
		CONNECTED,
		AUTHENTICATED,
		PUBLISHING,
		RECEIVING
	};

	Client() : m_network(0), m_protocol(new Protocol()),
		m_state(NOT_CONNECTED) {}
	~Client() {
		if (m_network != 0)
			delete m_network;
		if (m_protocol != 0)
			delete m_protocol;
	}
	state& get_state();
	boost::signals2::signal<void (char**, size_t*)>& get_sig();
	void control(char**, size_t*);

private:
	Network*	m_network;
	Protocol*	m_protocol;
	state		m_state;
	boost::signals2::signal<void (char**, size_t*)>	m_sig;
};

#endif
