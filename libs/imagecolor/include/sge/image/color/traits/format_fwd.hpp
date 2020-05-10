//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_COLOR_TRAITS_FORMAT_FWD_HPP_INCLUDED
#define SGE_IMAGE_COLOR_TRAITS_FORMAT_FWD_HPP_INCLUDED

#include <sge/image/color/format_fwd.hpp>
#include <sge/image/color/tag.hpp>
#include <sge/image/traits/pixel/format_tpl_fwd.hpp>


namespace sge
{
namespace image
{
namespace traits
{
namespace pixel
{

template<>
struct format_tpl<
	sge::image::color::tag
>
{
	using
	type
	=
	sge::image::color::format;
};

}
}
}
}

#endif
