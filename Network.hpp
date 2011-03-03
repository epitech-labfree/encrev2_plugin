#ifndef ENCREV2_PLUGIN_NETWORK_HH_
# define ENCREV2_PLUGIN_NETWORK_HH_

#include <iostream>
# include <string>
# include <boost/asio.hpp>
# include <boost/thread.hpp>
# include <boost/utility.hpp>
# include <boost/signals2.hpp>
using boost::asio::ip::tcp;

/*
 * Receiver concept:
 * receive_data(std::vector<unsigned char>*)
 */

template<class Receiver>
class Network : boost::noncopyable {
public:
	enum state {
		ERROR,
		CONNECTED,
		NOT_CONNECTED
	};

	Network(const std::string& host, short int port)
	       : m_state(NOT_CONNECTED), m_socket(0), m_buff(0), m_receiver(0), m_io_service()
	{
		//m_io_service = boost::asio::io_service();
		//tcp::resolver resolver(m_io_service);
		//tcp::resolver::query query(tcp::v4(), host, port); // TODO: Ipv6
		//tcp::resolver::iterator iterator = resolver.resolve(query);
		
		m_socket = new tcp::socket(m_io_service);
		//m_socket->connect(*iterator);

		std::clog << "test" << std::endl;
		m_endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(host), port);
		std::clog << "test" << std::endl;
		m_socket->async_connect(m_endpoint, boost::bind(&Network::connect_handler, this,
						boost::asio::placeholders::error));
	}

	~Network() {
		delete m_socket;
		delete m_buff;
		m_socket = 0;
		m_buff = 0;
	}

	void write(char* buff, size_t size) {
		if (m_state != CONNECTED)
			return;

		async_write(*m_socket, boost::asio::buffer(buff, size),
				boost::bind(&Network::write_handler, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
	}

	void write(const std::string& buff) {
		using namespace boost::asio;

		if (m_state != CONNECTED)
			return;
		async_write(*m_socket, buffer(buff),
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

		std::cout << "Network::read" << std::endl;
		m_buff = new std::vector<unsigned char>(size);
		async_read(*m_socket, buffer(*m_buff, size), transfer_all(),
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
	void run() {
		std::clog << "Encre::Network Thread started" << std::endl;
		boost::system::error_code ec;
		m_io_service.run(ec);
		std::clog << "Encre::Network Run finnish: " << ec.message() << std::endl;
	}

	void	connect_handler(const boost::system::error_code& error) {
		if (!error) {
			m_thread = boost::thread(boost::bind(&Network<Receiver>::run, this));
			m_state = CONNECTED;
			std::clog << "Encre::Network Connection Success" << std::endl;
		}
		else {
			m_state = ERROR;
			std::clog << "Encre::Network Connection Failed" << std::endl;
		}	
	}

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
				m_buff = 0;
			}
		}
		else
		{
			std::cout << "Error in read_handler: " << error.message() << std::endl;
			delete m_buff;
			m_buff = 0;
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
	state				m_state;
	tcp::socket*			m_socket;
	std::vector<unsigned char>*	m_buff;
	Receiver*			m_receiver;
	boost::asio::io_service		m_io_service;
	boost::thread			m_thread;
	boost::asio::ip::tcp::endpoint  m_endpoint;
};

#endif
