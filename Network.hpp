#ifndef ENCREV2_PLUGIN_NETWORK_HH_
# define ENCREV2_PLUGIN_NETWORK_HH_

# include <string>
# include <boost/asio.hpp>
# include <boost/utility.hpp>
# include <boost/signals2.hpp>
using boost::asio::ip::tcp;

/*
 * Receiver concept:
 * receive_data(std::vector<unsigned char>*)
 * 
 *
 */

template<class Receiver>
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
		if (m_buff != 0)
			delete m_buff;
	}
	
	void		write(void*, size_t);
	void		write(const std::string&);
	void		read(size_t);
	
	state&	get_state() {
		return m_state;
	}
	
	void	set_receiver(Receiver* r) {
		m_receiver = r;
	}

protected:
	Network();
	void	read_handler(const boost::system::error_code&,
				size_t);
	void	write_handler(const boost::system::error_code&,
				size_t);

private:
	state		m_state;
	tcp::socket*	m_socket;
	std::vector<unsigned char>*	m_buff;
	Receiver*	m_receiver;
};

#endif
