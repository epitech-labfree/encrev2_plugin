#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include "Network.hh"

using boost::asio::ip::tcp;

Network::Network(const std::string& host, uint16_t port) :
	m_state(Network::NOT_CONNECTED), m_socket(0)
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
		std::cerr << "Encre::Network, Can't connect to " << host << std::endl;
		m_state = Network::ERROR;
	}
	m_state = Network::CONNECTED;
	std::clog << "Encre::Network, Connection" << std::endl;
}

Network::state&
Network::get_state()
{
	return m_state;
}

size_t
Network::write(void* buff, size_t size) {
	if (m_state != Network::CONNECTED)
		return 0;
	return boost::asio::write(*m_socket, boost::asio::buffer(buff, size));
}

size_t
Network::write(const std::string& buff) {
	if (m_state != Network::CONNECTED)
		return 0;
	return boost::asio::write(*m_socket, boost::asio::buffer(buff.c_str(),
				buff.size()));
}

size_t
Network::read(void* buff, size_t size) {
	try {
		if (m_socket != 0)
			return boost::asio::read(*m_socket,
					boost::asio::buffer(buff, size));
	}
	catch (...) {
		return 0;
	}
	return 0;
}
