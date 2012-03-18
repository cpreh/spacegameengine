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


#include <sge/renderer/parameters.hpp>
#include <sge/systems/optional_name.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/viewport/resize_function.hpp>
#include <fcppt/string.hpp>
#include <fcppt/math/box/object_impl.hpp>


sge::systems::renderer::renderer(
	sge::renderer::parameters const &_parameters,
	sge::viewport::resize_function const &_resize_function
)
:
	parameters_(_parameters),
	resize_function_(_resize_function),
	name_()
{
}

sge::systems::renderer &
sge::systems::renderer::name(
	fcppt::string const &_name
)
{
	name_ = _name;

	return *this;
}

sge::renderer::parameters const &
sge::systems::renderer::parameters() const
{
	return parameters_;
}

sge::viewport::resize_function const &
sge::systems::renderer::resize_function() const
{
	return resize_function_;
}

sge::systems::optional_name const &
sge::systems::renderer::name() const
{
	return name_;
}
