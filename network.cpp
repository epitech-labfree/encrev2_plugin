#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include "network.hh"

using boost::asio::ip::tcp;

Network* Network::_instance = 0;
bool Network::_is_connected = false;
tcp::socket* Network::_socket = 0;

Network*
Network::getInstance() {
	if (Network::_instance == 0)
		Network::_instance = new Network();
	return Network::_instance;
}

void
Network::kill() {
	if (Network::_instance != 0)
		delete Network::_instance;
}

void
Network::connect(const std::string& host, const std::string& port) {
        if (Network::_is_connected == true) {
	  	std::clog << "Encre::Network, already connected" << std::endl;
		return;
        }
	try {
	boost::asio::io_service io_service;
	tcp::resolver resolver(io_service);
	tcp::resolver::query query(tcp::v4(), host, port);
	tcp::resolver::iterator iterator = resolver.resolve(query);
	_socket = new tcp::socket(io_service);
	_socket->connect(*iterator);
	}
	catch (...) {
	  std::cerr << "Encre::Network, Can't connect to " << host << std::endl;
		return ;
	}
	std::clog << "Encre::Network, Connection" << std::endl;
	_is_connected = true;
}

tcp::socket*
Network::getSocket() const {
	return _socket;
}

void
Network::write(void* buff, size_t size) {
	if (_socket != 0)
		boost::asio::write(*_socket, boost::asio::buffer(buff, size));
}

void
Network::write(const std::string& buff) {
	if (_socket != 0)
		boost::asio::write(*_socket, boost::asio::buffer(buff.c_str(), buff.size()));
}
void
Network::write(char buff[]) {
	std::clog << sizeof(buff) << std::endl;
	if (_socket != 0)
		boost::asio::write(*_socket, boost::asio::buffer(buff, sizeof(buff)));
}
size_t
Network::read(void* buff, size_t size) {
	if (_socket != 0)
		return boost::asio::read(*_socket, boost::asio::buffer(buff, size));
	return 0;
}

void
Network::disconnect() {
	if (_is_connected == false)
		return ;
	_is_connected = false;
	try {
		_socket->close();
	}
	catch (...) {
		std::cerr << "Encre::Network, can't close socket" << std::endl;
	}
}

bool
Network::isConnected() const {
	return _is_connected;
}
