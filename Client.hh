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

	Client(const std::string& host, short int port);

	~Client()
	{
		delete m_network;
		delete m_protocol;
		m_network = 0;
		m_protocol = 0;
		EncreLog(EncreLog::Debug) << "Client: deleted";
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
		EncreLog() << "Client: state = RECEIVING";
	}

	void
	receive_data(encre::buffer_ptr buff) {
		m_buffers.push_back(buff);
	}
	
	bool
	is_data_received() const {
		return m_buffers.size() != 0;
	}
	
	void	send_data(char*, size_t);
	void	get_data(char**, size_t*);

protected:
	Client();

private:
	Network<Client>*	m_network;
	Protocol*		m_protocol;
	state			m_state;
	encre::buffer_list 	m_buffers;
};

#endif
