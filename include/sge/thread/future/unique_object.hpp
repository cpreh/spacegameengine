#ifndef SGE_THREAD_FUTURE_UNIQUE_OBJECT_HPP_INCLUDED
#define SGE_THREAD_FUTURE_UNIQUE_OBJECT_HPP_INCLUDED

#include <sge/thread/future/object.hpp>
#include <sge/thread/future/promise_fwd.hpp>
#include <sge/thread/unique_lock_mutex.hpp>
#include <sge/noncopyable.hpp>

namespace sge
{
namespace thread
{
namespace future
{
template<typename T>
class unique_object
:
	public object<T>
{
private:
	typedef object<T> base_type;
public:
	T &get();
private:
	friend class promise<T>;

	explicit unique_object(
		typename base_type::state_ptr const &);
};
}
}
}

template<typename T>
T &sge::thread::future::unique_object<T>::get()
{
	unique_lock_mutex l(
		base_type::state_->mutex_);
	base_type::state_->wait_and_check(
		l);
	return base_type::state_->result_;
}

template<typename T>
sge::thread::future::unique_object<T>::unique_object(
	typename base_type::state_ptr const &_state)
:
	base_type(
		_state)
{
}

#endif
