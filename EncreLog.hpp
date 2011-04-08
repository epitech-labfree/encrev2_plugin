#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#ifndef _ENCREV2_LOG_HPP___HH_
#define _ENCREV2_LOG_HPP___HH_

class EncreLog {
public:
	enum EncreMsgType {Note, Debug, Warning, Error};

	EncreLog() : _type(Note), _buffer(), _file(0) {}

	EncreLog(EncreMsgType type) : _type(type), _buffer(), _file(0) {}
	EncreLog(const char* file) : _type(Note), _buffer(), _file(file) {}
	EncreLog(const EncreLog& other) {
		if (&other != this) {
			std::string out = other._buffer.str();
			_buffer << out;
		}
	}

	virtual ~EncreLog() {
		std::string out = _buffer.str();

	      	switch (_type) {
		case Debug:
			out.insert(0, "DEBUG: ");
			break ;
		case Warning:
			out.insert(0, "WARN : ");
			break ;
		case Error:
			out.insert(0, "ERROR: ");
			break ;
		case Note:
			out.insert(0, "NOTE : ");
		default :
			break ;

		}
		if (_file == 0)
			std::clog << out << std::endl;
		else {
			std::filebuf fb;
			fb.open (_file, std::ios::out);
			std::ostream os(&fb);
			os << out;
			fb.close();
		}
	}

	template<typename T> inline EncreLog&
	operator<<(T t) {
		_buffer << t;
		return *this;
	}

private:
 	EncreMsgType _type;
	std::stringstream _buffer;
	const char* _file;
};

template<> inline EncreLog&
EncreLog::operator<< (char c) {
	_buffer << "'" << c << "'";
	return *this;
}

template<> inline EncreLog&
EncreLog::operator<<(bool b) {
	_buffer << (b == true ? "true" : "false");
	return *this;
}

#endif
