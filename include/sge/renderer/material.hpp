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


#ifndef SGE_RENDERER_MATERIAL_HPP_INCLUDED
#define SGE_RENDERER_MATERIAL_HPP_INCLUDED

#include <sge/image/color/any/object.hpp>
#include <sge/renderer/ambient_color.hpp>
#include <sge/renderer/diffuse_color.hpp>
#include <sge/renderer/emissive_color.hpp>
#include <sge/renderer/material_fwd.hpp>
#include <sge/renderer/shininess.hpp>
#include <sge/renderer/specular_color.hpp>
#include <sge/renderer/symbol.hpp>
#include <fcppt/variant/object_impl.hpp>


namespace sge
{
namespace renderer
{

/**
 * \brief Describes how light affects geometry
 *
 * A material describes how light affects geometry if lighting and fixed
 * function pipeline are enabled. The closer a color is to white the more a
 * specific component of a light affects the geometry.
 *
 * \see renderer::light
 * \see renderer::state::bool_::enable_lighting
*/
class material
{
public:
	/**
	 * \brief Constructs a material
	 *
	 * \param diffuse Describes how much diffuse light affects geometry
	 *
	 * \param ambient Describes how much ambient light affects geometry
	 *
	 * \param specular Describes how much specular light affects geometry
	 *
	 * \param emissive Describes how much geometry shines in the absence of light
	 *
	 * \param shininess Describes how strong specular light is
	*/
	SGE_RENDERER_SYMBOL
	material(
		renderer::diffuse_color const &diffuse,
		renderer::ambient_color const &ambient,
		renderer::specular_color const &specular,
		renderer::emissive_color const &emissive,
		renderer::shininess shininess
	);

	/**
	 * \brief Returns the diffuse part
	*/
	SGE_RENDERER_SYMBOL
	renderer::diffuse_color const &
	diffuse() const;

	/**
	 * \brief Returns the ambient part
	*/
	SGE_RENDERER_SYMBOL
	renderer::ambient_color const &
	ambient() const;

	/**
	 * \brief Returns the specular part
	*/
	SGE_RENDERER_SYMBOL
	renderer::specular_color const &
	specular() const;

	/**
	 * \brief Returns the emissive part
	*/
	SGE_RENDERER_SYMBOL
	renderer::emissive_color const &
	emissive() const;

	/**
	 * \brief Returns the shininess
	*/
	SGE_RENDERER_SYMBOL
	renderer::shininess const
	shininess() const;
private:
	renderer::diffuse_color diffuse_;

	renderer::ambient_color ambient_;

	renderer::specular_color specular_;

	renderer::emissive_color emissive_;

	renderer::shininess shininess_;
};

}
}

#endif
