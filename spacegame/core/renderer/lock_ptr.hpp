#ifndef SGE_LOCK_PTR_HPP_INCLUDED
#define SGE_LOCK_PTR_HPP_INCLUDED

#include "./renderer_types.hpp"

namespace sge
{

template<typename T> class lock_ptr {
public:
	lock_ptr(T t, lock_flag_t flags = LF_Default)
		: t(t)
	{
		t->lock(flags);
	}
	~lock_ptr()
	{
		t->unlock();
	}
private:
	T t;
};


}

#endif
