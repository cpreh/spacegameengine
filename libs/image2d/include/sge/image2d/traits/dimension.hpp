//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE2D_TRAITS_DIMENSION_HPP_INCLUDED
#define SGE_IMAGE2D_TRAITS_DIMENSION_HPP_INCLUDED

#include <sge/image/dimension_integral_c.hpp>
#include <sge/image/traits/image/dimension_tpl_fwd.hpp>
#include <sge/image2d/tag.hpp>


namespace sge
{
namespace image
{
namespace traits
{
namespace image
{

template<>
struct dimension_tpl<
	sge::image2d::tag
>
{
	typedef
	sge::image::dimension_integral_c<
		2
	>
	type;
};

}
}
}
}

#endif
