#include <sge/thread/atomic_flag.hpp>
#include <sge/thread/lock_guard_mutex.hpp>

sge::thread::atomic_flag::atomic_flag(
	bool _flag)
:
	mutex_(),
	flag_(
		_flag)
{
}

bool sge::thread::atomic_flag::test_and_set()
{
	lock_guard_mutex l(
		mutex_);
	bool old_flag = flag_;
	flag_ = true;
	return old_flag;
}

void sge::thread::atomic_flag::clear()
{
	lock_guard_mutex l(
		mutex_);
	flag_ = false;
}
