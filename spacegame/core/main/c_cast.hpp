#ifndef SGE_C_CAST_HPP_INCLUDED
#define SGE_C_CAST_HPP_INCLUDED

namespace sge
{
	template<typename IncompatibleType, typename Source> IncompatibleType c_cast(const Source& s)
	{
		return (IncompatibleType)s;
	}
}

#endif

