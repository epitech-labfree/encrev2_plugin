#ifndef ENCREV2_PLUGIN_NETWORK_HH_
# define ENCREV2_PLUGIN_NETWORK_HH_

#include "Buffer.hh"
# include <iostream>
# include <string>
# include <boost/asio.hpp>
# include <boost/utility.hpp>
# include <boost/bind.hpp>
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
		NOT_CONNECTED,
		CONNECTED
	};

	Network(const std::string& host, short int port)
	       : m_state(NOT_CONNECTED), m_socket(0), m_buff(0), m_receiver(0), m_io_service()
	{
		m_socket = new tcp::socket(m_io_service);

		m_endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(host), port);
		m_socket->async_connect(m_endpoint, boost::bind(&Network::connect_handler, this,
						boost::asio::placeholders::error));
		std::cout << "NOTE: Network created" << std::endl;
	}

	~Network() {
		m_socket.shutdown();
		delete m_socket;
		delete m_buff;
		m_socket = 0;
		m_buff = 0;
		std::cout << "NOTE: Network deleted" << std::endl;
	}

	void write(char* buff, size_t size) {
		if (m_state != CONNECTED)
			return;

		async_write(*m_socket, boost::asio::buffer(buff, size),
				boost::bind(&Network::write_handler, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
	}

	void read(size_t size) {
		using namespace boost::asio;

		if (m_state != CONNECTED)
			return ;
		if (m_buff != 0)
			std::clog << "ERROR: Network::read: m_buff already assigned." << std::endl;

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
		std::clog << "DEBUG: Network::set_receiver" << std::endl;
		m_receiver = r;
	}

private:
	Network();
	void run() {
		std::clog << "NOTE: Network::run started" << std::endl;
		boost::system::error_code ec;
		size_t num = m_io_service.run(ec);
		std::clog << "NOTE: Network::run finished: " << ec.message() << " . After " << num << "handler" << std::endl;
	}

protected:
	void	connect_handler(const boost::system::error_code& error) {
		std::clog << "DEBUG: Network::connect_handler: call" << std::endl;
		if (!error) {
			m_state = CONNECTED;
			m_receiver->set_state((size_t)CONNECTED);
			std::clog << "NOTE: Network Connection Success" << std::endl;
		}
		else {
			m_state = ERROR;
			m_receiver->set_state(ERROR);
			std::clog << "NOTE: Network Connection Failed" << std::endl;
		}
	}

	void	read_handler(const boost::system::error_code& error,
		size_t transferred)
	{
		if (!error)
		{
			std::clog << "DEBUG: Network::handle_read: bytes read " << transferred << std::endl;
			if (m_receiver)
				m_receiver->receive_data(m_buff);
			else {
				std::clog << "DEBUG: Network::handle_read: No one to transmit data." << std::endl;
				delete m_buff;
				m_buff = 0;
			}
		}
		else
		{
			std::clog << "ERROR: Network::handle_read: " << error.message() << std::endl;
			delete m_buff;
			m_buff = 0;
		}
	}

	void write_handler(const boost::system::error_code&
		error, size_t transferred)
	{
		if (!error)
		{
			std::clog << "NOTE: Network::write_handler: bytes write " << transferred << std::endl;
		}
		else
		{
			std::clog << "ERROR: Network::write_handler: " << error.message() << std::endl;
		}
		exit (0);
	}

private:
	state				m_state;
	tcp::socket*			m_socket;
	encre::const_buffer_list	m_buffers;
	encre::buffer_ptr		m_input_buffer;
	Receiver*			m_receiver;
	boost::asio::io_service		m_io_service;
	boost::asio::ip::tcp::endpoint  m_endpoint;
};

#endif
