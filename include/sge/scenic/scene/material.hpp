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


#ifndef SGE_SCENIC_SCENE_MATERIAL_HPP_INCLUDED
#define SGE_SCENIC_SCENE_MATERIAL_HPP_INCLUDED

#include <sge/renderer/material.hpp>
#include <sge/scenic/symbol.hpp>
#include <sge/scenic/scene/identifier.hpp>
#include <sge/scenic/scene/diffuse_texture_path.hpp>
#include <sge/scenic/scene/specular_texture_path.hpp>


namespace sge
{
namespace scenic
{
namespace scene
{
class material
{
public:
	SGE_SCENIC_SYMBOL
	material(
		sge::scenic::scene::identifier const &,
		sge::renderer::material const &,
		sge::scenic::scene::diffuse_texture_path const &,
		sge::scenic::scene::specular_texture_path const &);

	SGE_SCENIC_SYMBOL
	sge::scenic::scene::identifier const &
	identifier() const;

	SGE_SCENIC_SYMBOL
	sge::renderer::material const &
	renderer_material() const;

	SGE_SCENIC_SYMBOL
	sge::scenic::scene::diffuse_texture_path const &
	diffuse_texture() const;

	SGE_SCENIC_SYMBOL
	sge::scenic::scene::specular_texture_path const &
	specular_texture() const;
private:
	sge::scenic::scene::identifier identifier_;
	sge::renderer::material renderer_material_;
	sge::scenic::scene::diffuse_texture_path diffuse_texture_;
	sge::scenic::scene::specular_texture_path specular_texture_;
};
}
}
}

#endif
