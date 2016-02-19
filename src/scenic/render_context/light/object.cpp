/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/scenic/render_context/light/object.hpp>

sge::scenic::render_context::light::object::object(
	sge::scenic::render_context::diffuse_color const &_diffuse_color,
	sge::scenic::render_context::specular_color const &_specular_color,
	sge::scenic::render_context::ambient_color const &_ambient_color,
	sge::scenic::render_context::light::variant const &_variant)
:
	diffuse_color_(
		_diffuse_color),
	specular_color_(
		_specular_color),
	ambient_color_(
		_ambient_color),
	variant_(
		_variant)
{
}

sge::scenic::render_context::diffuse_color const &
sge::scenic::render_context::light::object::diffuse_color() const
{
	return
		diffuse_color_;
}

sge::scenic::render_context::specular_color const &
sge::scenic::render_context::light::object::specular_color() const
{
	return
		specular_color_;
}

sge::scenic::render_context::ambient_color const &
sge::scenic::render_context::light::object::ambient_color() const
{
	return
		ambient_color_;
}

sge::scenic::render_context::light::variant const &
sge::scenic::render_context::light::object::variant() const
{
	return
		variant_;
}
