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


#include <sge/scenic/scene/material/object.hpp>

sge::scenic::scene::material::object::object(
	sge::scenic::scene::identifier const &_identifier,
	sge::scenic::scene::material::diffuse_color const &_diffuse_color,
	sge::scenic::scene::material::ambient_color const &_ambient_color,
	sge::scenic::scene::material::specular_color const &_specular_color,
	sge::scenic::scene::material::emissive_color const &_emissive_color,
	sge::scenic::scene::material::shininess const &_shininess,
	sge::scenic::scene::material::diffuse_texture_path const &_diffuse_texture,
	sge::scenic::scene::material::specular_texture_path const &_specular_texture)
:
	identifier_(
		_identifier),
	diffuse_color_(
		_diffuse_color),
	ambient_color_(
		_ambient_color),
	specular_color_(
		_specular_color),
	emissive_color_(
		_emissive_color),
	shininess_(
		_shininess),
	diffuse_texture_(
		_diffuse_texture),
	specular_texture_(
		_specular_texture)
{
}

sge::scenic::scene::identifier const &
sge::scenic::scene::material::object::identifier() const
{
	return
		identifier_;
}

sge::scenic::scene::material::diffuse_color const &
sge::scenic::scene::material::object::diffuse_color() const
{
	return
		diffuse_color_;
}

sge::scenic::scene::material::ambient_color const &
sge::scenic::scene::material::object::ambient_color() const
{
	return
		ambient_color_;
}

sge::scenic::scene::material::specular_color const &
sge::scenic::scene::material::object::specular_color() const
{
	return
		specular_color_;
}

sge::scenic::scene::material::emissive_color const &
sge::scenic::scene::material::object::emissive_color() const
{
	return
		emissive_color_;
}

sge::scenic::scene::material::shininess const &
sge::scenic::scene::material::object::shininess() const
{
	return
		shininess_;
}

sge::scenic::scene::material::diffuse_texture_path const &
sge::scenic::scene::material::object::diffuse_texture() const
{
	return
		diffuse_texture_;
}

sge::scenic::scene::material::specular_texture_path const &
sge::scenic::scene::material::object::specular_texture() const
{
	return
		specular_texture_;
}
