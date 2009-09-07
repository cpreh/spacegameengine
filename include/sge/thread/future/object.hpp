#ifndef SGE_THREAD_FUTURE_OBJECT_HPP_INCLUDED
#define SGE_THREAD_FUTURE_OBJECT_HPP_INCLUDED

#include <sge/thread/future/state.hpp>
#include <sge/shared_ptr.hpp>
#include <sge/noncopyable.hpp>

namespace sge
{
namespace thread
{
namespace future
{
template<typename T>
class object
{
SGE_NONCOPYABLE(object)
protected:
	typedef shared_ptr<state<T> > state_ptr;
	state_ptr state_;

	object(
		state_ptr const &);
public:
	bool is_ready() const;
	bool has_exception() const;
	bool has_value() const;
	void wait() const;
};
}
}
}

template<typename T>
sge::thread::future::object<T>::object(
	state_ptr const &_state)
:
	state_(
		_state)
{
}

template<typename T>
bool sge::thread::future::object<T>::is_ready() const
{
	return state_->is_ready();
}

template<typename T>
bool sge::thread::future::object<T>::has_exception() const
{
	return state_->has_exception();
}

template<typename T>
bool sge::thread::future::object<T>::has_value() const
{
	return state_->has_value();
}

template<typename T>
void sge::thread::future::object<T>::wait() const
{
	state_->wait();
}

#endif
