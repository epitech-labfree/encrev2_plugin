#ifndef ENCREV2_PLUGIN_NETWORK_HH_
#define ENCREV2_PLUGIN_NETWORK_HH_

#include <boost/asio.hpp>
using boost::asio::ip::tcp;

class Network {
	public:
	Network();
	virtual ~Network() {}
  	void		connect(const std::string&, const std::string&);
  	void		disconnect();
  	tcp::socket* 	getSocket() const;
	void		write(void*, size_t);
	void		write(char []);
	void		write(const std::string&);
	size_t		read(void*, size_t);
	bool		isConnected() const;

	protected:
	Network(const Network&);
	Network&
	operator=(const Network&);

	public:

	private:
	tcp::socket*		_socket;
	bool			_is_connected;
};

#endif
