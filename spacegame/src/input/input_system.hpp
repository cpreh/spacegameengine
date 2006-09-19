#ifndef SGE_INPUT_SYSTEM_HPP_INCLUDED
#define SGE_INPUT_SYSTEM_HPP_INCLUDED

#include <boost/utility.hpp>
#include <boost/signal.hpp>
#include <boost/signals/connection.hpp>
#include "../shared_ptr.hpp"
#include "./key_type.hpp"
#include "./callback_handle.hpp"

namespace sge
{

class input_system : boost::noncopyable {
public:
	typedef boost::signal< void (const key_pair&)> signal_type;
	typedef boost::function<void (const key_pair&)> callback;

	virtual callback_handle register_callback(const callback& c) = 0;
	virtual void dispatch() = 0;
	virtual ~input_system() {}
};
typedef shared_ptr<input_system> input_system_ptr;

}

#endif
