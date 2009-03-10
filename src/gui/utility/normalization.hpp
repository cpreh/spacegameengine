#ifndef SGE_GUI_UTILITY_NORMALIZATION_HPP_INCLUDED
#define SGE_GUI_UTILITY_NORMALIZATION_HPP_INCLUDED

#include <limits>

namespace sge
{
namespace gui
{
namespace utility
{
template<typename Dest,typename Src>
Dest normalize(Src const &s)
{
	return static_cast<Dest>(
		(static_cast<Dest>(s) - static_cast<Dest>(std::numeric_limits<Src>::min()))/
		(static_cast<Dest>(static_cast<Dest>(std::numeric_limits<Src>::max()) - static_cast<Dest>(std::numeric_limits<Src>::min()))));
}

template<typename Dest,typename Src>
Dest denormalize(Src const &s)
{
	return static_cast<Dest>(
		s*static_cast<Src>(static_cast<Src>(std::numeric_limits<Dest>::max())-static_cast<Src>(std::numeric_limits<Dest>::min()))+static_cast<Src>(std::numeric_limits<Dest>::min()));
}
}
}
}

#endif
