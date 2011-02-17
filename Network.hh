#ifndef ENCREV2_PLUGIN_NETWORK_HH_
# define ENCREV2_PLUGIN_NETWORK_HH_

# include <string>
# include <boost/asio.hpp>
# include <boost/utility.hpp>
# include <boost/signals2.hpp>
using boost::asio::ip::tcp;

class Network : boost::noncopyable {
public:
	enum state {
		ERROR,
		CONNECTED,
		NOT_CONNECTED
	};

	Network(const std::string&, uint16_t port);
	
	~Network() {
		if (m_socket != 0)
			delete m_socket;
	}
	
	size_t		write(void*, size_t);
	size_t		write(const std::string&);
	size_t		read(void*, size_t);
	state&		get_state();

protected:
	Network();

private:
	state		m_state;
	tcp::socket*	m_socket;
};

#endif
