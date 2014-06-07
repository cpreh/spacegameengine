/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_MODEL_OBJ_MATERIAL_OBJECT_HPP_INCLUDED
#define SGE_MODEL_OBJ_MATERIAL_OBJECT_HPP_INCLUDED

#include <sge/model/obj/identifier.hpp>
#include <sge/model/obj/symbol.hpp>
#include <sge/model/obj/material/ambient_color.hpp>
#include <sge/model/obj/material/diffuse_color.hpp>
#include <sge/model/obj/material/diffuse_texture_path.hpp>
#include <sge/model/obj/material/emissive_color.hpp>
#include <sge/model/obj/material/shininess.hpp>
#include <sge/model/obj/material/specular_color.hpp>
#include <sge/model/obj/material/specular_texture_path.hpp>


namespace sge
{
namespace model
{
namespace obj
{
namespace material
{
class object
{
public:
	SGE_MODEL_OBJ_SYMBOL
	object(
		sge::model::obj::identifier const &,
		sge::model::obj::material::diffuse_color const &,
		sge::model::obj::material::ambient_color const &,
		sge::model::obj::material::specular_color const &,
		sge::model::obj::material::emissive_color const &,
		sge::model::obj::material::shininess const &,
		sge::model::obj::material::diffuse_texture_path const &,
		sge::model::obj::material::specular_texture_path const &);

	SGE_MODEL_OBJ_SYMBOL
	sge::model::obj::identifier const &
	identifier() const;

	SGE_MODEL_OBJ_SYMBOL
	sge::model::obj::material::diffuse_color const &
	diffuse_color() const;

	SGE_MODEL_OBJ_SYMBOL
	sge::model::obj::material::ambient_color const &
	ambient_color() const;

	SGE_MODEL_OBJ_SYMBOL
	sge::model::obj::material::specular_color const &
	specular_color() const;

	SGE_MODEL_OBJ_SYMBOL
	sge::model::obj::material::emissive_color const &
	emissive_color() const;

	SGE_MODEL_OBJ_SYMBOL
	sge::model::obj::material::shininess const &
	shininess() const;

	SGE_MODEL_OBJ_SYMBOL
	sge::model::obj::material::diffuse_texture_path const &
	diffuse_texture() const;

	SGE_MODEL_OBJ_SYMBOL
	sge::model::obj::material::specular_texture_path const &
	specular_texture() const;
private:
	sge::model::obj::identifier identifier_;
	sge::model::obj::material::diffuse_color diffuse_color_;
	sge::model::obj::material::ambient_color ambient_color_;
	sge::model::obj::material::specular_color specular_color_;
	sge::model::obj::material::emissive_color emissive_color_;
	sge::model::obj::material::shininess shininess_;
	sge::model::obj::material::diffuse_texture_path diffuse_texture_;
	sge::model::obj::material::specular_texture_path specular_texture_;
};
}
}
}
}

#endif
