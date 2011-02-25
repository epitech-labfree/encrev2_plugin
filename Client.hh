#include <Network.hpp>
#include <Protocol.hh>
#include <vector>

# include <boost/signals2.hpp>

#ifndef ENCREV2_PLUGIN_CLIENT_HH
# define ENCREV2_PLUGIN_CLIENT_HH

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

	Client(const std::string& host, uint16_t port)
		: m_network(new Network<Client>(host, port)),
		m_protocol(new Protocol()), m_state(NOT_CONNECTED), m_buff(0)
	{
	}

	~Client()
	{
		delete m_network;
		delete m_protocol;
		delete m_buff;
		m_network == 0
		m_protocol = 0;
		m_buff = 0;
	}

	Client::state&
	get_state() {
		return m_state;
	}
	
	void
	send_data(char* buf, size_t size) const {
		m_network->write(std::string(buf, size));
	}
	
	void
	receive_data(std::vector<unsigned char>* buff) {
		if (m_buff != 0)
			std::cerr << "Client::receive_data: Memory Leak" << std::endl;
		m_buff = new std::vector<unsigned char>(*buff);
		delete buff;
	}
	
	bool
	is_data_received() const {
		return m_buff != 0;
	}
	
	void	    get_data(char**, size_t*);

protected:
	Client();

private:
	Network<Client>*	m_network;
	Protocol*		m_protocol;
	state			m_state;
	std::vector<unsigned char>* m_buff;
};

#endif
