#include <sge/thread/future/state_base.hpp>
#include <sge/thread/future/error.hpp>
#include <sge/thread/unique_lock_mutex.hpp>
#include <sge/thread/lock_guard_mutex.hpp>
#include <sge/thread/copy_exception.hpp>
#include <boost/bind.hpp>

sge::thread::future::state_base::state_base()
:
	cond_(),
	error_(),
	ready_(
		false),
	retrieved_(
		false),
	mutex_()
{
}

bool sge::thread::future::state_base::is_ready()
{
	lock_guard_mutex l(
		mutex_);
	return ready_;
}

bool sge::thread::future::state_base::has_exception()
{
	lock_guard_mutex l(
		mutex_);
	return ready_ && error_;
}

bool sge::thread::future::state_base::has_value()
{
	lock_guard_mutex l(
		mutex_);
	return ready_ && !error_;
}

void sge::thread::future::state_base::wait()
{
	unique_lock_mutex l(
		mutex_);
	if (!ready_)
		cond_.wait(
			l,
			boost::bind(
				&state_base::ready,
				this));
}

void sge::thread::future::state_base::break_promise()
{
	{
		lock_guard_mutex l(
			mutex_);
		if (ready_)
			return;
		error_ = 
			copy_exception(
				error(
					error_code::broken_promise));
		ready_ = true;
	}
	cond_.notify_all();
}

void sge::thread::future::state_base::set_exception(
	exception_ptr _error)
{
	{
		lock_guard_mutex l(
			mutex_);
		set_ready_flag(
			l);
		error_ = _error;
	}
	cond_.notify_all();
}

void sge::thread::future::state_base::set_retrieved_flag()
{
	if (retrieved_.test_and_set())
		throw error(
			error_code::already_retrieved);
}

void sge::thread::future::state_base::wait_and_check(
	unique_lock_mutex &_l)
{
	if (!ready_)
		cond_.wait(
			_l,
			boost::bind(
				&state_base::ready,
				this));
}

void sge::thread::future::state_base::set_ready_flag(
	lock_guard_mutex &)
{
	if (ready_)
		throw error(
			error_code::promise_already_satisfied);
	ready_ = true;
}

bool sge::thread::future::state_base::ready() const
{
	return ready_;
}
