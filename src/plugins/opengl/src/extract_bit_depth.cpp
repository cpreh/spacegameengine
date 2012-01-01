/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/extract_bit_depth.hpp>
#include <sge/opengl/convert/bit_depth.hpp>
#include <sge/opengl/convert/visual_depth.hpp>
#include <sge/renderer/display_mode.hpp>
#include <sge/renderer/screen_mode.hpp>
#include <sge/renderer/visual_depth.hpp>
#include <awl/window/bit_depth.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/variant/object_impl.hpp>


namespace
{

struct visitor
{
	typedef awl::window::bit_depth::type result_type;

	result_type
	operator()(
		sge::renderer::display_mode const &
	) const;

	result_type
	operator()(
		sge::renderer::visual_depth::type
	) const;
};

}

awl::window::bit_depth::type
sge::opengl::extract_bit_depth(
	renderer::screen_mode const &_screen_mode
)
{
	return
		fcppt::variant::apply_unary(
			visitor(),
			_screen_mode
		);
}

namespace
{

visitor::result_type
visitor::operator()(
	sge::renderer::display_mode const &_display_mode
) const
{
	return
		sge::opengl::convert::bit_depth(
			_display_mode.bit_depth()
		);
}

visitor::result_type
visitor::operator()(
	sge::renderer::visual_depth::type const _visual_depth
) const
{
	return
		sge::opengl::convert::visual_depth(
			_visual_depth
		);
}

}
