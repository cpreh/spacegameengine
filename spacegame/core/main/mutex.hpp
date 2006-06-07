#ifndef SGE_MUTEX_HPP_INCLUDED
#define SGE_MUTEX_HPP_INCLUDED

#include "./types.hpp"
#include "./shared_ptr.hpp"

namespace sge
{
	class mutex {
	public:
		virtual void lock() = 0;
		virtual void unlock() = 0;
		virtual ~mutex(){}
	};

	typedef shared_ptr<mutex> mutex_ptr;
	COREDLLAPI mutex_ptr create_mutex();
}

#endif
