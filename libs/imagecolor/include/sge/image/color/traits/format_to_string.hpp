//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_COLOR_TRAITS_FORMAT_TO_STRING_HPP_INCLUDED
#define SGE_IMAGE_COLOR_TRAITS_FORMAT_TO_STRING_HPP_INCLUDED

#include <sge/image/color/format_fwd.hpp>
#include <sge/image/color/tag.hpp>
#include <sge/image/color/detail/symbol.hpp>
#include <sge/image/traits/pixel/format_to_string_tpl_fwd.hpp>
#include <fcppt/string.hpp>


namespace sge::image::traits::pixel
{

template<>
struct format_to_string_tpl<
	sge::image::color::tag
>
{
	SGE_IMAGE_COLOR_DETAIL_SYMBOL
	static
	fcppt::string
	execute(
		sge::image::color::format
	);
};

}

#endif
