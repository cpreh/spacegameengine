//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE3D_TRAITS_COLOR_TAG_HPP_INCLUDED
#define SGE_IMAGE3D_TRAITS_COLOR_TAG_HPP_INCLUDED

#include <sge/image/color/tag.hpp>
#include <sge/image/traits/image/color_tag_tpl_fwd.hpp>
#include <sge/image3d/tag.hpp>


namespace sge::image::traits::image
{

template<>
struct color_tag_tpl<
	sge::image3d::tag
>
{
	using
	type
	=
	sge::image::color::tag;
};

}

#endif
