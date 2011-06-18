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


#include <sge/renderer/light/object.hpp>

sge::renderer::light::object::object(
	renderer::diffuse_color const &_diffuse,
	renderer::specular_color const &_specular,
	renderer::ambient_color const &_ambient,
	light::variant const &_variant
)
:
	diffuse_(_diffuse),
	specular_(_specular),
	ambient_(_ambient),
	variant_(_variant)
{
}

sge::renderer::diffuse_color const &
sge::renderer::light::object::diffuse() const
{
	return diffuse_;
}

sge::renderer::specular_color const &
sge::renderer::light::object::specular() const
{
	return specular_;
}

sge::renderer::ambient_color const &
sge::renderer::light::object::ambient() const
{
	return ambient_;
}

sge::renderer::light::variant const &
sge::renderer::light::object::variant() const
{
	return variant_;
}
