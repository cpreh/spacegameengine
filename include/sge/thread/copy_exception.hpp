#ifndef SGE_THREAD_COPY_EXCEPTION_HPP_INCLUDED
#define SGE_THREAD_COPY_EXCEPTION_HPP_INCLUDED

#include <sge/exception_ptr.hpp>

namespace sge
{
namespace thread
{
template<typename E>
exception_ptr copy_exception(E e)
{
	return 
		exception_ptr(
			new E(
				e));
}
}
}

#endif
