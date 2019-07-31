//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/line_drawer/color.hpp>
#include <sge/line_drawer/line.hpp>
#include <sge/renderer/vector3.hpp>


sge::line_drawer::line::line(
	sge::renderer::vector3 const &_begin,
	sge::renderer::vector3 const &_end
)
:
	sge::line_drawer::line::line(
		_begin,
		_end,
		sge::image::color::any::object{
			sge::image::color::predef::white()
		},
		sge::image::color::any::object{
			sge::image::color::predef::white()
		}
	)
{
}

sge::line_drawer::line::line(
	sge::renderer::vector3 const &_begin,
	sge::renderer::vector3 const &_end,
	sge::image::color::any::object const &_begin_color,
	sge::image::color::any::object const &_end_color
)
:
	begin_(
		_begin
	),
	end_(
		_end
	),
	begin_color_(
		sge::image::color::any::convert<
			color_format
		>(
			_begin_color
		)
	),
	end_color_(
		sge::image::color::any::convert<
			color_format
		>(
			_end_color
		)
	)
{
}

sge::renderer::vector3 const &
sge::line_drawer::line::begin() const
{
	return
		begin_;
}

sge::renderer::vector3 const &
sge::line_drawer::line::end() const
{
	return end_;
}

sge::line_drawer::color const &
sge::line_drawer::line::begin_color() const
{
	return
		begin_color_;
}

sge::line_drawer::color const &
sge::line_drawer::line::end_color() const
{
	return
		end_color_;
}
