#ifndef SGE_THREAD_HPP_INCLUDED
#define SGE_THREAD_HPP_INCLUDED

#include <string>
#include "./types.hpp"
#include "./shared_ptr.hpp"
#include <stdexcept>
#include <limits>

namespace sge
{
	class thread {
	public:
		virtual void stop() = 0;
		virtual void resume() = 0;
		virtual void kill() = 0;
		virtual bool wait_for_me(ulong milli_seconds = std::numeric_limits<ulong>::max()) = 0;
		virtual ~thread() {}
	};

	class thread_function {
	public:
		virtual ulong operator()() = 0;
	};

	typedef shared_ptr<thread> thread_ptr;
	COREDLLAPI thread_ptr create_thread(thread_function& fun);
}

#endif
