#ifndef ENCREV2_PLUGIN_NETWORK_HH_
# define ENCREV2_PLUGIN_NETWORK_HH_

#include "Buffer.hh"
# include <iostream>
# include <string>
# include <boost/asio.hpp>
# include <boost/utility.hpp>
# include <boost/bind.hpp>
# include <boost/thread.hpp>
# include <boost/shared_ptr.hpp>
using boost::asio::ip::tcp;

/*
 * Receiver concept:
 * receive_data(std::vector<unsigned char>*)
 */

#define READ_SIZE 1024

template<class Receiver>
class Network : boost::noncopyable {
public:
	enum state {
		ERROR,
		NOT_CONNECTED,
		CONNECTED
	};

	Network(const std::string& host, short int port)
	       : m_state(NOT_CONNECTED), m_socket(0), m_receiver(0), m_io_service(), m_buffers()
	{
		m_socket = new tcp::socket(m_io_service);

		m_endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(host), port);
		m_socket->async_connect(m_endpoint, boost::bind(&Network::connect_handler, this,
						boost::asio::placeholders::error));

		m_thread = boost::thread(boost::bind(&Network<Receiver>::run, this));
		std::cout << "DEBUG: Network created" << std::endl;
	}

	~Network() {
		m_socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both);
		delete m_socket;
		m_socket = 0;
		std::cout << "DEBUG: Network deleted" << std::endl;
	}

	void write(const char* buff, size_t size) {
		if (m_state != CONNECTED || m_buffers.size() == 0)
			return;

		async_write(*m_socket, boost::asio::buffer(buff, size),
				boost::bind(&Network::write_handler, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
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

	void read(size_t size) {
		using namespace boost::asio;

		if (m_state != CONNECTED)
			return ;

		encre::buffer_ptr p(new encre::buffer(size));
		m_buffers.push_back(p);
		async_read(*m_socket, buffer(*p.get()), transfer_all(),
				boost::bind(&Network::read_handler, this,
					placeholders::error,
					placeholders::bytes_transferred));
	}

private:
	Network();
	void run() {
		std::clog << "DEBUG: Network::run started" << std::endl;
		boost::system::error_code ec;
		size_t num = m_io_service.run(ec);
		std::clog << "DEBUG: Network::run finished: " << ec.message() << " . After " << num << " handler" << std::endl;
	}

protected:
	void	connect_handler(const boost::system::error_code& error) {
		if (!error) {
			m_state = CONNECTED;
			m_receiver->set_state((size_t)CONNECTED);
			std::clog << "NOTE: Network state = CONNECTED" << std::endl;
			Network::read(READ_SIZE);
		}
		else {
			m_state = ERROR;
			m_receiver->set_state(ERROR);
			std::clog << "NOTE: Network state = ERROR" << std::endl;
		}
	}

	void	read_handler(const boost::system::error_code& error, size_t transferred) {
		if (!error) {
			std::clog << "DEBUG: Network::handle_read: bytes read " << transferred << std::endl;
			if (m_receiver) {
				encre::buffer_ptr p = m_buffers.front();
				m_buffers.pop_front();
				p->resize(transferred);
				m_receiver->receive_data(p);
			}
			read(READ_SIZE);
		}
		else {
			std::clog << "ERROR: Network::handle_read: " << error.message() << std::endl;
		}
	}

	void write_handler(const boost::system::error_code&
		error, size_t transferred)
	{
		if (error)
			std::clog << "ERROR: Network::write_handler: " << error.message() << std::endl;

	}

private:
	state				m_state;
	tcp::socket*			m_socket;
	Receiver*			m_receiver;
	boost::asio::io_service		m_io_service;
	boost::asio::ip::tcp::endpoint  m_endpoint;
	encre::buffer_list		m_buffers;
	boost::thread                   m_thread;
};

#endif
