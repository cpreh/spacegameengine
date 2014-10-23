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


#ifndef SGE_SCENIC_SCENE_MATERIAL_OBJECT_HPP_INCLUDED
#define SGE_SCENIC_SCENE_MATERIAL_OBJECT_HPP_INCLUDED

#include <sge/scenic/detail/symbol.hpp>
#include <sge/scenic/scene/identifier.hpp>
#include <sge/scenic/scene/material/ambient_color.hpp>
#include <sge/scenic/scene/material/diffuse_color.hpp>
#include <sge/scenic/scene/material/diffuse_texture_path.hpp>
#include <sge/scenic/scene/material/emissive_color.hpp>
#include <sge/scenic/scene/material/shininess.hpp>
#include <sge/scenic/scene/material/specular_color.hpp>
#include <sge/scenic/scene/material/specular_texture_path.hpp>


namespace sge
{
namespace scenic
{
namespace scene
{
namespace material
{
class object
{
public:
	SGE_SCENIC_DETAIL_SYMBOL
	object(
		sge::scenic::scene::identifier const &,
		sge::scenic::scene::material::diffuse_color const &,
		sge::scenic::scene::material::ambient_color const &,
		sge::scenic::scene::material::specular_color const &,
		sge::scenic::scene::material::emissive_color const &,
		sge::scenic::scene::material::shininess const &,
		sge::scenic::scene::material::diffuse_texture_path const &,
		sge::scenic::scene::material::specular_texture_path const &);

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::scene::identifier const &
	identifier() const;

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::scene::material::diffuse_color const &
	diffuse_color() const;

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::scene::material::ambient_color const &
	ambient_color() const;

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::scene::material::specular_color const &
	specular_color() const;

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::scene::material::emissive_color const &
	emissive_color() const;

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::scene::material::shininess const &
	shininess() const;

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::scene::material::diffuse_texture_path const &
	diffuse_texture() const;

	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::scene::material::specular_texture_path const &
	specular_texture() const;
private:
	sge::scenic::scene::identifier identifier_;
	sge::scenic::scene::material::diffuse_color diffuse_color_;
	sge::scenic::scene::material::ambient_color ambient_color_;
	sge::scenic::scene::material::specular_color specular_color_;
	sge::scenic::scene::material::emissive_color emissive_color_;
	sge::scenic::scene::material::shininess shininess_;
	sge::scenic::scene::material::diffuse_texture_path diffuse_texture_;
	sge::scenic::scene::material::specular_texture_path specular_texture_;
};
}
}
}
}

#endif
