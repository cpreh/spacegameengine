//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/color/rgba32f.hpp>
#include <sge/image/color/rgba32f_format.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/scenic/impl/render_context/cg/any_color_to_vector4.hpp>
#include <mizuiro/color/object.hpp>
#include <mizuiro/color/channel/alpha.hpp>
#include <mizuiro/color/channel/blue.hpp>
#include <mizuiro/color/channel/green.hpp>
#include <mizuiro/color/channel/red.hpp>
#include <fcppt/math/vector/object_impl.hpp>


sge::renderer::vector4
sge::scenic::impl::render_context::cg::any_color_to_vector4(
	sge::image::color::any::object const &_any_color)
{
	sge::image::color::rgba32f const converted(
		sge::image::color::any::convert<sge::image::color::rgba32f_format>(
			_any_color));

	return
		sge::renderer::vector4(
			converted.get(
				mizuiro::color::channel::red()),
			converted.get(
				mizuiro::color::channel::green()),
			converted.get(
				mizuiro::color::channel::blue()),
			converted.get(
				mizuiro::color::channel::alpha()));
}
