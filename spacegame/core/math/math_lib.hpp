#ifndef SGE_MATH_LIB_HPP_INCLUDED
#define SGE_MATH_LIB_HPP_INCLUDED

#include "../main/types.hpp"

namespace sge
{
	class math_lib {
	public:
		SGECOREDLLAPI static void init();
		SGECOREDLLAPI static bool sse_avail();
	private:
		static bool initialized;
		static bool sse_available;
		math_lib();
		math_lib(const math_lib&);
		math_lib& operator= (const math_lib&);
		~math_lib();
	};
}

#endif
