#ifndef SGE_THREAD_FUTURE_STATE_HPP_INCLUDED
#define SGE_THREAD_FUTURE_STATE_HPP_INCLUDED

#include <sge/thread/future/state_base.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace sge
{
namespace thread
{
namespace future
{
template<typename T>
struct state
:
	state_base
{
	typename boost::remove_reference<T>::type result_;
};
}
}
}

#endif
