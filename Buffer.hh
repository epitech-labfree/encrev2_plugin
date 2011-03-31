#ifndef ENCREV2_BUFFER_HH
#define ENCREV2_BUFFER_HH

#include <vector>
#include <list>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace encre {
	typedef std::vector<unsigned char> buffer;
	typedef boost::shared_ptr<buffer>  buffer_ptr;
	typedef boost::shared_ptr<const buffer>  const_buffer_ptr;
	typedef std::list<buffer_ptr> buffer_list;
	typedef std::list<const_buffer_ptr> const_buffer_list;
};

#endif
