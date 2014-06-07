/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/image/color/rgba32f.hpp>
#include <sge/image/color/rgba32f_format.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/src/scenic/render_context/cg/any_color_to_vector4.hpp>
#include <mizuiro/color/object.hpp>
#include <mizuiro/color/channel/alpha.hpp>
#include <mizuiro/color/channel/blue.hpp>
#include <mizuiro/color/channel/green.hpp>
#include <mizuiro/color/channel/red.hpp>
#include <fcppt/math/vector/object_impl.hpp>


sge::renderer::vector4 const
sge::scenic::render_context::cg::any_color_to_vector4(
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
