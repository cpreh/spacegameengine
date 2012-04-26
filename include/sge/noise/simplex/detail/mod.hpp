#ifndef SGE_NOISE_SIMPLEX_DETAIL_MOD_HPP_INCLUDED
#define SGE_NOISE_SIMPLEX_DETAIL_MOD_HPP_INCLUDED

#include <cstddef>

namespace sge
{
namespace noise
{
namespace simplex
{
namespace detail
{

inline
std::size_t
mod(
	long const &a,
	std::size_t const &b)
{
	if (a >= 0)
		return static_cast<std::size_t>(a) %
			static_cast<std::size_t>(b);
	else
		return static_cast<std::size_t>(-a) %
			static_cast<std::size_t>(b);
}

}
}
}
}

#endif

