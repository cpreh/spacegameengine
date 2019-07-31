//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/to_color_value.hpp>
#include <sge/image/color/rgba32f.hpp>
#include <sge/image/color/rgba32f_format.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <mizuiro/color/channel/alpha.hpp>
#include <mizuiro/color/channel/blue.hpp>
#include <mizuiro/color/channel/green.hpp>
#include <mizuiro/color/channel/red.hpp>


D3DCOLORVALUE
sge::d3d9::convert::to_color_value(
	sge::image::color::any::object const &_color
)
{
	sge::image::color::rgba32f const conv(
		sge::image::color::any::convert<
			sge::image::color::rgba32f_format
		>(
			_color
		)
	);

	return
		D3DCOLORVALUE{
			conv.get(
				mizuiro::color::channel::red()
			),
			conv.get(
				mizuiro::color::channel::green()
			),
			conv.get(
				mizuiro::color::channel::blue()
			),
			conv.get(
				mizuiro::color::channel::alpha()
			)
		};
}
