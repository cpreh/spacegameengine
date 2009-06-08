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
#include <sge/text.hpp>

sge::string const
sge::window::parameters::default_class(
	SGE_TEXT("sgeclass"));

sge::window::parameters::parameters(
	string const &title_,
	string const &class_name_)
:
	title_(title_),
	dim_(),
	class_name_(class_name_)
{}

sge::window::parameters::parameters(
	string const &title_,
	dim_type const &dim_,
	string const &class_name_)
:
	title_(title_),
	dim_(dim_),
	class_name_(class_name_)
{}

sge::string const &
sge::window::parameters::title() const
{
	return title_;
}

sge::string const &
sge::window::parameters::class_name() const
{
	return class_name_;
}

sge::window::parameters::optional_dim const &
sge::window::parameters::dim() const
{
	return dim_;
}

void
sge::window::parameters::dim(
	dim_type const &d)
{
	dim_ = d;
}
