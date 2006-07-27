#ifndef SGE_INPUT_SYSTEM_HPP_INCLUDED
#define SGE_INPUT_SYSTEM_HPP_INCLUDED

#include <boost/utility.hpp>
#include "../main/shared_ptr.hpp"
#include "./key_type.hpp"

namespace sge
{

class input_system : boost::noncopyable {
public:
	typedef boost::function<void (const key_pair&)> callback;
	virtual callback_handle register_callback(const callback& c, const key_range& r) = 0;
	virtual ~input_system() {}
};
typedef shared_ptr<input_system> input_system_ptr;

}

#endif
