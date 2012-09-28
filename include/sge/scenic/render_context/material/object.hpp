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


#ifndef SGE_SCENIC_RENDER_CONTEXT_MATERIAL_OBJECT_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_MATERIAL_OBJECT_HPP_INCLUDED

#include <sge/scenic/symbol.hpp>
#include <sge/scenic/render_context/ambient_color.hpp>
#include <sge/scenic/render_context/diffuse_color.hpp>
#include <sge/scenic/render_context/emissive_color.hpp>
#include <sge/scenic/render_context/specular_color.hpp>
#include <sge/scenic/render_context/material/diffuse_texture.hpp>
#include <sge/scenic/render_context/material/shininess.hpp>
#include <sge/scenic/render_context/material/specular_texture.hpp>


namespace sge
{
namespace scenic
{
namespace render_context
{
namespace material
{
class object
{
public:
	SGE_SCENIC_SYMBOL
	object(
		sge::scenic::render_context::diffuse_color const &,
		sge::scenic::render_context::ambient_color const &,
		sge::scenic::render_context::specular_color const &,
		sge::scenic::render_context::emissive_color const &,
		sge::scenic::render_context::material::shininess const &,
		sge::scenic::render_context::material::diffuse_texture const &,
		sge::scenic::render_context::material::specular_texture const &);

	SGE_SCENIC_SYMBOL
	sge::scenic::render_context::diffuse_color const &
	diffuse_color() const;

	SGE_SCENIC_SYMBOL
	sge::scenic::render_context::ambient_color const &
	ambient_color() const;

	SGE_SCENIC_SYMBOL
	sge::scenic::render_context::specular_color const &
	specular_color() const;

	SGE_SCENIC_SYMBOL
	sge::scenic::render_context::emissive_color const &
	emissive_color() const;

	SGE_SCENIC_SYMBOL
	sge::scenic::render_context::material::shininess const &
	shininess() const;

	SGE_SCENIC_SYMBOL
	sge::scenic::render_context::material::diffuse_texture const &
	diffuse_texture() const;

	SGE_SCENIC_SYMBOL
	sge::scenic::render_context::material::specular_texture const &
	specular_texture() const;

	SGE_SCENIC_SYMBOL
	bool
	operator==(
		sge::scenic::render_context::material::object const &) const;
private:
	sge::scenic::render_context::diffuse_color diffuse_color_;
	sge::scenic::render_context::ambient_color ambient_color_;
	sge::scenic::render_context::specular_color specular_color_;
	sge::scenic::render_context::emissive_color emissive_color_;
	sge::scenic::render_context::material::shininess shininess_;
	sge::scenic::render_context::material::diffuse_texture diffuse_texture_;
	sge::scenic::render_context::material::specular_texture specular_texture_;
};
}
}
}
}

#endif
