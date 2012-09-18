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


#include <sge/renderer/adapter.hpp>
#include <sge/renderer/device/parameters.hpp>
#include <sge/renderer/parameters/object.hpp>
#include <awl/window/object_fwd.hpp>


sge::renderer::device::parameters::parameters(
	sge::renderer::adapter const _adapter,
	sge::renderer::parameters::object const &_params,
	awl::window::object &_window
)
:
	adapter_(
		_adapter
	),
	params_(
		_params
	),
	window_(
		_window
	)
{
}

sge::renderer::adapter const
sge::renderer::device::parameters::adapter() const
{
	return adapter_;
}

sge::renderer::parameters::object const &
sge::renderer::device::parameters::params() const
{
	return params_;
}

awl::window::object &
sge::renderer::device::parameters::window() const
{
	return window_;
}
