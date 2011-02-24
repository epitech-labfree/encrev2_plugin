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
		if (m_network != 0)
			delete m_network;
		if (m_protocol != 0)
			delete m_protocol;
		if (m_buff != 0)
			delete m_buff;
	}
	inline state& get_state();
	
	inline void send_data(char*, size_t) const;
	inline void receive_data(std::vector<unsigned char>*);
	inline bool is_data_received() const;
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
