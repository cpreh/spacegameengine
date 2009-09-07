#ifndef SGE_THREAD_FUTURE_PROMISE_HPP_INCLUDED
#define SGE_THREAD_FUTURE_PROMISE_HPP_INCLUDED

#include <sge/thread/future/state.hpp>
#include <sge/thread/lock_guard_mutex.hpp>
#include <sge/noncopyable.hpp>
#include <sge/shared_ptr.hpp>
#include <sge/exception_ptr.hpp>

namespace sge
{
namespace thread
{
namespace future
{
template<typename T>
class promise
{
SGE_NONCOPYABLE(promise)
public:
	promise();
	~promise();
	unique_object<T> get_future();
	void set_value(
		T const &);
	void set_exception(
		exception_ptr);
private:
	shared_ptr<state<T> > future_;
};
}
}
}

template<typename T>
sge::thread::future::promise<T>::promise()
:
	future_(
		new state<T>())
{
}

template<typename T>
sge::thread::future::promise<T>::~promise()
{
	if (future_ && !future_.unique())
		future_->break_promise();
}

template<typename T>
sge::thread::future::unique_object<T> sge::thread::future::promise<T>::get_future()
{
	return 
		unique_object<T>(
			future_);
}

template<typename T>
void sge::thread::future::promise<T>::set_value(
	T const &_result)
{
	{
		lock_guard_mutex l(
			future_->mutex_);
		future_->set_ready_flag(
			l);
		future_->result_ = _result;
	}
	future_->cond_.notify_all();
}

template<typename T>
void sge::thread::future::promise<T>::set_exception(
	exception_ptr _exception)
{
	future_->set_exception(
		_exception);
}

#endif
