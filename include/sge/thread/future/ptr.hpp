#ifndef SGE_THREAD_FUTURE_PTR_HPP_INCLUDED
#define SGE_THREAD_FUTURE_PTR_HPP_INCLUDED

#include "result_base.hpp"
#include <sge/shared_ptr.hpp>

namespace sge
{
namespace thread
{
namespace future
{
template<typename R>
struct ptr
{
	typedef shared_ptr<R, result_base::deleter> type;
};
}
}
}

#endif
