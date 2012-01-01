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


#include <sge/renderer/material.hpp>

sge::renderer::material::material(
	renderer::diffuse_color const &_diffuse,
	renderer::ambient_color const &_ambient,
	renderer::specular_color const &_specular,
	renderer::emissive_color const &_emissive,
	renderer::shininess const _shininess
)
:
	diffuse_(_diffuse),
	ambient_(_ambient),
	specular_(_specular),
	emissive_(_emissive),
	shininess_(_shininess)
{}

sge::renderer::diffuse_color const &
sge::renderer::material::diffuse() const
{
	return diffuse_;
}

sge::renderer::ambient_color const &
sge::renderer::material::ambient() const
{
	return ambient_;
}

sge::renderer::specular_color const &
sge::renderer::material::specular() const
{
	return specular_;
}

sge::renderer::emissive_color const &
sge::renderer::material::emissive() const
{
	return emissive_;
}

sge::renderer::shininess const
sge::renderer::material::shininess() const
{
	return shininess_;
}
