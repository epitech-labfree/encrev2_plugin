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

	Client(const std::string& host, short int port)
		: m_network(new Network<Client>(host, port)),
		m_protocol(new Protocol()), m_state(NOT_CONNECTED), m_buff(0)
	{
		switch (m_network->get_state()) {
			case Network<Client>::CONNECTED:
				m_state = CONNECTED;
				break;
			case Network<Client>::NOT_CONNECTED: // We probably have to handle it differently in the futur
			case Network<Client>::ERROR:
			default:
				m_state = ERROR;
		}
	}

	~Client()
	{
		delete m_network;
		delete m_protocol;
		delete m_buff;
		m_network = 0;
		m_protocol = 0;
		m_buff = 0;
	}

	Client::state&
	get_state() {
		return m_state;
	}

	void
	control() {
			m_network->write(std::string("GET toto\n\n", 10)); //XXX: CRAP
			m_state = RECEIVING;
			m_network->read(4096);
	}
	
	void
	send_data(char* buf, size_t size) {
		if (m_state == CONNECTED && m_protocol->foo()) {
			m_state = PUBLISHING;
			m_network->write(std::string("PUT toto\n\n", 10)); //XXX: CRAP
			goto write;
		}
		else if (m_state == PUBLISHING) {
			goto write;
		}
		else {
			std::cout << "Client::send_data error" << std::endl;
			return ;
		}
	write:
		m_network->write(buf, size);
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
