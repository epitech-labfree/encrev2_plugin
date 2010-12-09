#include <iostream>
#include <map>
#include <utility>
#include <string>
#include "encrev2_CliOpt.hh"

VlcCliOpt::VlcCliOpt() : _opt() {}
VlcCliOpt::~VlcCliOpt() {}

void
VlcCliOpt::set_option(const std::string& global_option,
    const std::string& option,
    const std::string& value) {

	std::string key(option.c_str());
	key.append("=");
	key.append(value.c_str());
	_opt.insert(std::pair<std::string, std::string>(global_option, key));
}

std::string&
VlcCliOpt::get_option() {
	std::string str("#");
	std::multimap<std::string, std::string>::iterator it = _opt.begin();

	while (it != _opt.end()) {
		std::cout << (*it).first << " => " << (*it).second << std::endl;
		for (unsigned int i = 0; i != _opt.count((*it).first); ++it);
	}
	return str;
}
