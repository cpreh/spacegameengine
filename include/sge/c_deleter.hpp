#ifndef SGE_C_DELETER_HPP_INCLUDED
#define SGE_C_DELETER_HPP_INCLUDED

#include <cstdlib>

namespace sge
{
template<typename T>
class c_deleter {
public:
	void operator()(T *const t) const
	{
		std::free(t);
	}
};
}

#endif
