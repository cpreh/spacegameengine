/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/parameters/object.hpp>
#include <sge/renderer/parameters/vsync.hpp>
#include <sge/renderer/pixel_format/object.hpp>


sge::renderer::parameters::object::object(
	sge::renderer::pixel_format::object const &_pixel_format,
	sge::renderer::parameters::vsync const _vsync,
	sge::renderer::display_mode::optional_object const &_display_mode
)
:
	pixel_format_(
		_pixel_format
	),
	vsync_(
		_vsync
	),
	display_mode_(
		_display_mode
	)
{
}

sge::renderer::pixel_format::object const &
sge::renderer::parameters::object::pixel_format() const
{
	return pixel_format_;
}

sge::renderer::parameters::vsync
sge::renderer::parameters::object::vsync() const
{
	return vsync_;
}

sge::renderer::display_mode::optional_object const
sge::renderer::parameters::object::display_mode() const
{
	return display_mode_;
}
