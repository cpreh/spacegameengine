//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE2D_TRAITS_COLOR_TAG_HPP_INCLUDED
#define SGE_IMAGE2D_TRAITS_COLOR_TAG_HPP_INCLUDED

#include <sge/image/color/tag.hpp>
#include <sge/image/traits/image/color_tag_tpl_fwd.hpp>
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
struct color_tag_tpl<
	sge::image2d::tag
>
{
	typedef
	sge::image::color::tag
	type;
};

}
}
}
}

#endif
