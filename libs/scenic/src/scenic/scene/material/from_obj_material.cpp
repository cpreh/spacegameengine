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


#include <sge/scenic/scene/identifier.hpp>
#include <sge/scenic/scene/material/ambient_color.hpp>
#include <sge/scenic/scene/material/diffuse_color.hpp>
#include <sge/scenic/scene/material/emissive_color.hpp>
#include <sge/scenic/scene/material/diffuse_texture_path.hpp>
#include <sge/scenic/scene/material/from_obj_material.hpp>
#include <sge/scenic/scene/material/specular_color.hpp>
#include <sge/scenic/scene/material/specular_texture_path.hpp>
#include <sge/scenic/scene/material/shininess.hpp>
#include <sge/scenic/scene/material/object.hpp>


sge::scenic::scene::material::object
sge::scenic::scene::material::from_obj_material(
	sge::model::obj::material::object const &_material
)
{
	return
		sge::scenic::scene::material::object(
			sge::scenic::scene::identifier(
				_material.identifier().get()
			),
			sge::scenic::scene::material::diffuse_color(
				_material.diffuse_color().get()
			),
			sge::scenic::scene::material::ambient_color(
				_material.ambient_color().get()
			),
			sge::scenic::scene::material::specular_color(
				_material.specular_color().get()
			),
			sge::scenic::scene::material::emissive_color(
				_material.emissive_color().get()
			),
			sge::scenic::scene::material::shininess(
				_material.shininess().get()
			),
			sge::scenic::scene::material::diffuse_texture_path(
				_material.diffuse_texture().get()
			),
			sge::scenic::scene::material::specular_texture_path(
				_material.specular_texture().get()
			))
		;
}
