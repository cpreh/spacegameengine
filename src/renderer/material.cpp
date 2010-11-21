/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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
	image::color::any::object const &diffuse_,
	image::color::any::object const &ambient_,
	image::color::any::object const &specular_,
	image::color::any::object const &emissive_,
	scalar const &power_)
:
	diffuse_(diffuse_),
	ambient_(ambient_),
	specular_(specular_),
	emissive_(emissive_),
	power_(power_)
{}

sge::image::color::any::object const &
sge::renderer::material::diffuse() const
{
	return diffuse_;
}

sge::image::color::any::object const &
sge::renderer::material::ambient() const
{
	return ambient_;
}

sge::image::color::any::object const &
sge::renderer::material::specular() const
{
	return specular_;
}

sge::image::color::any::object const &
sge::renderer::material::emissive() const
{
	return emissive_;
}

sge::renderer::scalar const &
sge::renderer::material::power() const
{
	return power_;
}
