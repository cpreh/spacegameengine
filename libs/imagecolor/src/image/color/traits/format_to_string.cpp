//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/color/format.hpp>
#include <sge/image/color/format_to_string.hpp>
#include <sge/image/color/tag.hpp>
#include <sge/image/color/traits/format_to_string.hpp>
#include <fcppt/string.hpp>


fcppt::string
sge::image::traits::pixel::format_to_string_tpl<
	sge::image::color::tag
>::execute(
	sge::image::color::format const _format
)
{
	return
		sge::image::color::format_to_string(
			_format
		);
}
