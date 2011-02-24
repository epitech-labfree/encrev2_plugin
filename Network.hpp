#ifndef ENCREV2_PLUGIN_NETWORK_HH_
# define ENCREV2_PLUGIN_NETWORK_HH_

#include <iostream>
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

	Network(const std::string& host, unsigned short port) :
		m_state(NOT_CONNECTED), m_socket(0), m_buff(0), m_receiver(0)
	{
		try {
			boost::asio::io_service io_service;
			tcp::resolver resolver(io_service);
			tcp::resolver::query query(tcp::v4(), host, port);
			tcp::resolver::iterator iterator = resolver.resolve(query);
			m_socket = new tcp::socket(io_service);
			m_socket->connect(*iterator);
		}
		catch (...) {
			std::cerr << "Encre::Network, Can't connect to " << host <<
				std::endl;
			m_state = ERROR;
		}
		m_state = CONNECTED;
		std::clog << "Encre::Network, Connection" << std::endl;
	}

	~Network() {
		if (m_socket != 0)
			delete m_socket;
		if (m_buff != 0)
			delete m_buff;
	}

	void write(void* buff, size_t size) {
		using namespace boost::asio;

		if (m_state != CONNECTED)
			return;

		async_write(*m_socket, buffer(buff, size),
				boost::bind(&Network::write_handler, this,
					placeholders::error,
					placeholders::bytes_transferred));
	}

	void write(const std::string& buff) {
		using namespace boost::asio;

		if (m_state != CONNECTED)
			return;

		async_write(*m_socket, buffer(buff.c_str(), buff.size()),
				boost::bind(&Network::write_handler, this,
					placeholders::error,
					placeholders::bytes_transferred));
	}

	void read(size_t size) {
		using namespace boost::asio;

		if (m_state != CONNECTED)
			return ;
		if (m_buff != 0)
			std::cerr << "m_buff already assigned. Check that !" << std::endl;

		m_buff = new std::vector<unsigned char>(size);
		async_read(*m_socket, buffer(*m_buff), transfer_all(),
				boost::bind(&Network::read_handler, this,
					placeholders::error,
					placeholders::bytes_transferred));
	}

	state&	get_state()
	{
		return m_state;
	}

	void	set_receiver(Receiver* r)
	{
		m_receiver = r;
	}

protected:
	Network();
	void	read_handler(const boost::system::error_code& error,
		size_t transferred)
	{
		if (!error)
		{
			std::cout << "handle_read: " << transferred << std::endl;
			if (m_receiver)
				m_receiver->receive_data(m_buff);
			else {
				std::cerr << "No one to transmit data." << std::endl;
				delete m_buff;
			}
		}
		else
		{
			std::cout << "Error in read_handler: " << error.message() << std::endl;
			delete m_buff;
		}
	}

	void write_handler(const boost::system::error_code&
		error, size_t transferred)
	{
		if (!error)
		{
			std::cout << "handle_write: " << transferred << std::endl;
		}
		else
		{
			std::cout << "Error in read_handler: " << error.message() << std::endl;
		}
	}

private:
	state		m_state;
	tcp::socket*	m_socket;
	std::vector<unsigned char>*	m_buff;
	Receiver*	m_receiver;
};

#endif