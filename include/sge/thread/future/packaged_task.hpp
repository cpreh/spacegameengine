#ifndef SGE_THREAD_FUTURE_PACKAGED_TASK_HPP_INCLUDED
#define SGE_THREAD_FUTURE_PACKAGED_TASK_HPP_INCLUDED

#include <sge/thread/future/unique_object.hpp>
#include <sge/noncopyable.hpp>
#include <boost/function.hpp>

namespace sge
{
namespace thread
{
namespace future
{
template<typename T>
class packaged_task
{
SGE_NONCOPYABLE(packaged_task)
public:
	typedef T result;
	typedef boost::function<result ()> task;

	explicit packaged_task(
		task const &);
	unique_object<result> get_future();
	void operator()();
private:
	task task_;
	promise<result> promise_;
};
}
}
}

template<typename T>
sge::thread::future::packaged_task<T>::packaged_task(
	task const &_task)
:
	task_(
		_task),
	promise_()
{
}

template<typename T>
sge::thread::future::unique_object<T> sge::thread::future::packaged_task<T>::get_future()
{
	return promise_.get_future();
}

template<typename T>
void sge::thread::future::packaged_task<T>::operator()()
{
	promise_.set_value(
		task_());
}

#endif
