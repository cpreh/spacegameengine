#ifndef SGE_THREAD_FUTURE_STATE_BASE_HPP_INCLUDED
#define SGE_THREAD_FUTURE_STATE_BASE_HPP_INCLUDED

#include <sge/thread/condition_variable.hpp>
#include <sge/thread/atomic_flag.hpp>
#include <sge/thread/unique_lock_mutex.hpp>
#include <sge/thread/lock_guard_mutex.hpp>
#include <sge/exception_ptr.hpp>
#include <sge/noncopyable.hpp>

namespace sge
{
namespace thread
{
namespace future
{
class state_base
{
SGE_NONCOPYABLE(state_base)
public:
	state_base();
	bool is_ready();
	bool has_exception();
	bool has_value();
	void wait();
	void break_promise();
	void set_exception(exception_ptr);
	void set_retrieved_flag();
	void wait_and_check(
		unique_lock_mutex &);
	void set_ready_flag(
		lock_guard_mutex &);
	mutex mutex_;
private:
	bool ready() const;

	condition_variable cond_;
	exception_ptr error_;
	bool ready_;
	atomic_flag retrieved_;
};
}
}
}

#endif
