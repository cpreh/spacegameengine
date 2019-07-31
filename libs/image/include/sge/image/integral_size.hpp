//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_INTEGRAL_SIZE_HPP_INCLUDED
#define SGE_IMAGE_INTEGRAL_SIZE_HPP_INCLUDED

#include <sge/image/size_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image
{

template<
	sge::image::size_type Size
>
using
integral_size
=
std::integral_constant<
	sge::image::size_type,
	Size
>;

}
}

#endif
