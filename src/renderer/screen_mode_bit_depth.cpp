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


#include <sge/renderer/bit_depth.hpp>
#include <sge/renderer/fullscreen.hpp>
#include <sge/renderer/screen_mode.hpp>
#include <sge/renderer/screen_mode_bit_depth.hpp>
#include <sge/renderer/windowed.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/variant/object_impl.hpp>


namespace
{

struct visitor
{
	typedef sge::renderer::bit_depth::type result_type;

	result_type
	operator()(
		sge::renderer::fullscreen const &
	) const;

	result_type
	operator()(
		sge::renderer::windowed const &
	) const;
};

}

sge::renderer::bit_depth::type
sge::renderer::screen_mode_bit_depth(
	sge::renderer::screen_mode const &_screen_mode
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
	sge::renderer::fullscreen const &_fullscreen
) const
{
	return
		_fullscreen.display_mode().bit_depth();
}

visitor::result_type
visitor::operator()(
	sge::renderer::windowed const &_windowed
) const
{
	return
		_windowed.bit_depth();
}

}
