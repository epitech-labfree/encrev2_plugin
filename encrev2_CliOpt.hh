#include <map>
#include <string>

#ifndef ENCREV2_CLIOPT_HH_
# define ENCREV2_CLIOPT_HH_

class VlcCliOpt {
	std::multimap<std::string, std::string> _opt;

public:
	void set_option(const std::string&, const std::string&, const std::string&);
	std::string& get_option();
	VlcCliOpt();
	virtual ~VlcCliOpt();
};


#endif /* !ENCREV2_CLIOPT_HH_ */
