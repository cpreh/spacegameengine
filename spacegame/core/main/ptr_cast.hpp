#ifndef SGE_PTR_CAST_HPP_INCLUDED
#define SGE_PTR_CAST_HPP_INCLUDED

#include <typeinfo>

namespace sge
{
	template<typename T, typename U> inline T ptr_cast (const U u)
	{
#ifndef SGE_FLAG_NORTTI
		if(!u)
			return 0;

		T t = dynamic_cast<T>(u);
		if(!t)
			throw std::bad_cast();
		return t;
#else
		return static_cast<T>(u);
#endif
	}
}

#endif
