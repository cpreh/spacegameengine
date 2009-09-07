#ifndef SGE_THREAD_ATOMIC_FLAG_HPP_INCLUDED
#define SGE_THREAD_ATOMIC_FLAG_HPP_INCLUDED

#include <sge/thread/mutex.hpp>
#include <sge/noncopyable.hpp>

namespace sge
{
namespace thread
{
class atomic_flag
{
SGE_NONCOPYABLE(atomic_flag)
public:
	atomic_flag(bool = false);
	bool test_and_set();
	void clear();
private:
	mutex mutex_;
	bool flag_;
};
}
}

#endif
