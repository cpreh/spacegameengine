//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/to_color.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/rgba8_format.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <mizuiro/color/channel/alpha.hpp>
#include <mizuiro/color/channel/blue.hpp>
#include <mizuiro/color/channel/green.hpp>
#include <mizuiro/color/channel/red.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


D3DCOLOR
sge::d3d9::convert::to_color(
	sge::image::color::any::object const &_color
)
{
	sge::image::color::rgba8 const conv(
		sge::image::color::any::convert<
			sge::image::color::rgba8_format
		>(
			_color
		)
	);

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)
	return
		D3DCOLOR_ARGB(
			conv.get(
				mizuiro::color::channel::alpha()
			),
			conv.get(
				mizuiro::color::channel::red()
			),
			conv.get(
				mizuiro::color::channel::green()
			),
			conv.get(
				mizuiro::color::channel::blue()
			)
		);
FCPPT_PP_POP_WARNING
}
