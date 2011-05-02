/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../extract_size.hpp"
#include <sge/renderer/display_mode.hpp>
#include <sge/renderer/screen_mode.hpp>
#include <sge/window/instance.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/variant/holds_type.hpp>
#include <fcppt/variant/object_impl.hpp>

sge::renderer::screen_size const
sge::d3d9::parameters::extract_size(
	renderer::screen_mode const &_screen_mode,
	sge::window::instance &_window
)
{
	return
		fcppt::variant::holds_type<
			sge::renderer::display_mode
		>(
			_screen_mode	
		)
		?
			_screen_mode.get<
				sge::renderer::display_mode
			>().size()
		:
			_window.size();
}
