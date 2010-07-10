/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/window/parameters.hpp>
#include <fcppt/text.hpp>

namespace
{

fcppt::string const
default_class(
	FCPPT_TEXT("sgeclass")
);

}

sge::window::parameters::parameters(
	fcppt::string const &_title
)
:
	title_(_title),
	class_name_(
		default_class
	),
	dim_(),
	io_service_()
{}

sge::window::parameters
sge::window::parameters::class_name(
	fcppt::string const &_class_name
)
{
	class_name_ = _class_name;

	return *this;
}

sge::window::parameters
sge::window::parameters::dim(
	dim_type const &_dim
)
{
	dim_ = _dim;

	return *this;
}

sge::window::parameters
sge::window::parameters::io_service(
	mainloop::io_service_ptr const _io_service
)
{
	io_service_ = _io_service;

	return *this;
}

fcppt::string const &
sge::window::parameters::title() const
{
	return title_;
}

fcppt::string const &
sge::window::parameters::class_name() const
{
	return class_name_;
}

sge::window::parameters::optional_dim const &
sge::window::parameters::dim() const
{
	return dim_;
}

sge::mainloop::io_service_ptr const
sge::window::parameters::io_service() const
{
	return io_service_;
}
