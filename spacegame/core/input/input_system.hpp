#ifndef SGE_INPUT_SYSTEM_HPP_INCLUDED
#define SGE_INPUT_SYSTEM_HPP_INCLUDED

#include <boost/utility.hpp>
#include "../main/shared_ptr.hpp"
#include "./key_type.hpp"

namespace sge
{
	class input_system : boost::noncopyable {
	public:
		virtual input_array get_input() = 0;
		virtual ~input_system() {}
	};
	typedef shared_ptr<input_system> input_system_ptr;
}

#endif
