#ifndef SGE_THREAD_LOCK_GUARD_MUTEX_HPP_INCLUDED
#define SGE_THREAD_LOCK_GUARD_MUTEX_HPP_INCLUDED

#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>

namespace sge
{
namespace thread
{
typedef boost::lock_guard<mutex> lock_guard_mutex;
}
}

#endif
