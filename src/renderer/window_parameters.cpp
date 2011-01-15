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


#include <sge/renderer/window_parameters.hpp>
#include <sge/window/default_class_name.hpp>
#include <fcppt/text.hpp>

sge::renderer::window_parameters::window_parameters(
	fcppt::string const &_title
)
:
	title_(_title),
	class_name_(
		sge::window::default_class_name()
	)
{}

sge::renderer::window_parameters &
sge::renderer::window_parameters::class_name(
	fcppt::string const &_class_name
)
{
	class_name_ = _class_name;

	return *this;
}

fcppt::string const &
sge::renderer::window_parameters::title() const
{
	return title_;
}

fcppt::string const &
sge::renderer::window_parameters::class_name() const
{
	return class_name_;
}
