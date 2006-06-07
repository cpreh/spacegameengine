#ifndef SGE_C_CAST_HPP_INCLUDED
#define SGE_C_CAST_HPP_INCLUDED

namespace sge
{
	template<typename Dest, typename Source> Dest c_cast(const Source& s)
	{
		return (Dest)s;
	}
}

#endif

