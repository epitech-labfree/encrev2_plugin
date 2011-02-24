#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/completion_condition.hpp>
#include "Network.hh"

using boost::asio::ip::tcp;

// This members functions are here for preventing auto-inlinning

template<class Receiver>
Network<Receiver>::Network(const std::string& host, uint16_t port) :
	m_state(Network<Receiver>::NOT_CONNECTED), m_socket(0), m_buff(0), m_receiver(0)
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
		m_state = Network<Receiver>::ERROR;
	}
	m_state = Network<Receiver>::CONNECTED;
	std::clog << "Encre::Network, Connection" << std::endl;
}

template<class Receiver> void
Network<Receiver>::write(void* buff, size_t size) {
	using namespace boost::asio;

	if (m_state != Network<Receiver>::CONNECTED)
		return;

	async_write(*m_socket, buffer(buff, size),
			boost::bind(&Network<Receiver>::write_handler, this,
				placeholders::error,
				placeholders::bytes_transferred));
}

template<class Receiver> void
Network<Receiver>::write(const std::string& buff) {
	using namespace boost::asio;

	if (m_state != Network<Receiver>::CONNECTED)
		return;

	async_write(*m_socket, buffer(buff.c_str(), buff.size()),
			boost::bind(&Network<Receiver>::write_handler, this,
				placeholders::error,
				placeholders::bytes_transferred));
}

template<class Receiver> void
Network<Receiver>::read(size_t size) {
	using namespace boost::asio;

	if (m_state != Network<Receiver>::CONNECTED)
		return ;
	if (m_buff != 0)
		std::cerr << "m_buff already assigned. Check that !" << std::endl;

	m_buff = new std::vector<unsigned char>(size);
	async_read(*m_socket, buffer(*m_buff), transfer_all(),
			boost::bind(&Network<Receiver>::read_handler, this,
				placeholders::error,
				placeholders::bytes_transferred));
}

template<class Receiver> void
Network<Receiver>::read_handler(const boost::system::error_code& error,
	      size_t transferred) {
	if (!error)
	{
		std::cout << "handle_read: " << transferred << std::endl;
		// Call someone here
	}
	else
	{
		std::cout << "Error in read_handler: " << error.message() << std::endl;
		delete m_buff;
	}
}

template<class Receiver> void
Network<Receiver>::write_handler(const boost::system::error_code&
		error, size_t transferred) {
	if (!error)
	{
		std::cout << "handle_write: " << transferred << std::endl;
	}
	else
	{
		std::cout << "Error in read_handler: " << error.message() << std::endl;
	}
}
