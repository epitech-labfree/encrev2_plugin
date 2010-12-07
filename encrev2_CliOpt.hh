#include <map>
#include <string>

#ifndef ENCREV2_CLIOPT_HH_
# define ENCREV2_CLIOPT_HH_

class VlcCliOpt {
	std::map<std::string, std::string> _opt;

	void initTranscode();

public:
	void set_option(const std::string&, const std::string&, const std::string&);
	VlcCliOpt();
	virtual ~VlcCliOpt();
};


#endif /* !ENCREV2_CLIOPT_HH_ */
