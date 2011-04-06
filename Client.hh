#include "Buffer.hh"
#include <Network.hpp>
#include <Protocol.hh>

# include <boost/shared_ptr.hpp>

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
		m_protocol(new Protocol()), m_state(NOT_CONNECTED), m_buffers()
	{
		switch (m_network->get_state()) {
			case Network<Client>::CONNECTED:
				m_state = CONNECTED;
				std::clog << "NOTE: Client: state = CONNECTED " << std::endl;
				break;
			case Network<Client>::NOT_CONNECTED:
				m_state = NOT_CONNECTED;
				std::clog << "NOTE: Client: state = NOT_CONNECTED" << std::endl;
				break;
			case Network<Client>::ERROR:
			default:
				m_state = ERROR;
				std::clog << "NOTE: Client: state = ERROR" << std::endl;
		}
		std::clog << "DEBUG: Client: created" << std::endl;
		m_network->set_receiver(this);
	}

	~Client()
	{
		delete m_network;
		delete m_protocol;
		m_network = 0;
		m_protocol = 0;
		std::clog << "DEBUG: Client: deleted" << std::endl;
	}

	Client::state&
	get_state() {
		return m_state;
	}

	void
	set_state(size_t nstate) {
		m_state = (state)nstate;
	}

	void
	control() {
		m_network->write("GET toto\n\n", 10); //XXX: CRAP
		m_state = RECEIVING;
		std::clog << "NOTE: Client: state = RECEIVING" << std::endl;
	}
	
	void
	send_data(char* buf, size_t size) {
		if (m_state == CONNECTED && m_protocol->foo()) { //TODO: Replace foo() by a parser
			m_state = PUBLISHING;
			m_network->write("PUT toto\n\n", 10); //XXX: CRAP
			std::clog << "NOTE: Client: state = PUBLISHING" << std::endl;
			goto write;
		}
		else if (m_state == PUBLISHING) {
			goto write;
		}
		else {
			return ;
		}
	write:
		m_network->write(buf, size);
	}
	
	void
	receive_data(encre::buffer_ptr buff) {
		m_buffers.push_back(buff);
	}
	
	bool
	is_data_received() const {
		return m_buffers.size() != 0;
	}
	
	void	    get_data(char**, size_t*);

protected:
	Client();

private:
	Network<Client>*	m_network;
	Protocol*		m_protocol;
	state			m_state;
	encre::buffer_list 	m_buffers;
};

#endif
