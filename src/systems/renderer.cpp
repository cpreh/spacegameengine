/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/plugin/name.hpp>
#include <sge/renderer/caps/system_field.hpp>
#include <sge/renderer/device/index.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/systems/optional_name.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/viewport/optional_resize_callback.hpp>


sge::systems::renderer::renderer(
	sge::renderer::pixel_format::object const &_pixel_format,
	sge::renderer::display_mode::parameters const &_display_mode,
	sge::viewport::optional_resize_callback const &_resize_callback
)
:
	pixel_format_(
		_pixel_format
	),
	display_mode_(
		_display_mode
	),
	resize_callback_(
		_resize_callback
	),
	caps_(
		sge::renderer::caps::system_field::null()
	),
	name_(),
	device_index_(
		0u
	)
{
}

sge::systems::renderer &
sge::systems::renderer::caps(
	sge::renderer::caps::system_field const &_caps
)
{
	caps_ =
		_caps;

	return
		*this;
}

sge::systems::renderer &
sge::systems::renderer::name(
	sge::plugin::name const &_name
)
{
	name_ =
		sge::systems::optional_name(
			_name
		);

	return
		*this;
}

sge::renderer::pixel_format::object const &
sge::systems::renderer::pixel_format() const
{
	return
		pixel_format_;
}

sge::renderer::display_mode::parameters const &
sge::systems::renderer::display_mode() const
{
	return
		display_mode_;
}

sge::viewport::optional_resize_callback const &
sge::systems::renderer::resize_callback() const
{
	return
		resize_callback_;
}

sge::renderer::caps::system_field const &
sge::systems::renderer::caps() const
{
	return
		caps_;
}

sge::systems::optional_name const &
sge::systems::renderer::name() const
{
	return
		name_;
}

sge::renderer::device::index
sge::systems::renderer::device_index() const
{
	return
		device_index_;
}
