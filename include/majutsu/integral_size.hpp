#ifndef MAJUTSU_INTEGRAL_SIZE_HPP_INCLUDED
#define MAJUTSU_INTEGRAL_SIZE_HPP_INCLUDED

#include <majutsu/size_type.hpp>
#include <boost/mpl/integral_c.hpp>

namespace majutsu
{

template<
	size_type Size
>
struct integral_size
:
boost::mpl::integral_c<
	size_type,
	Size
>
{};

}

#endif
