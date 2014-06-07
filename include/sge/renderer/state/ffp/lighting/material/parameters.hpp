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


#ifndef SGE_RENDERER_STATE_FFP_LIGHTING_MATERIAL_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_LIGHTING_MATERIAL_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/symbol.hpp>
#include <sge/renderer/state/ffp/lighting/ambient_color.hpp>
#include <sge/renderer/state/ffp/lighting/diffuse_color.hpp>
#include <sge/renderer/state/ffp/lighting/specular_color.hpp>
#include <sge/renderer/state/ffp/lighting/material/emissive_color.hpp>
#include <sge/renderer/state/ffp/lighting/material/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/material/shininess.hpp>


namespace sge
{
namespace renderer
{
namespace state
{
namespace ffp
{
namespace lighting
{
namespace material
{

/**
\brief Describes how light affects geometry

A material describes how light affects geometry if lighting is enabled. The
closer a color is to white the more a specific component of a light affects the
geometry.

*/
class parameters
{
public:
	/**
	\brief Constructs material parameters

	\param diffuse Describes how much diffuse light affects geometry

	\param ambient Describes how much ambient light affects geometry

	\param specular Describes how much specular light affects geometry

	\param emissive Describes how much geometry shines in the absence of light

	\param shininess Describes how strong specular light is
	*/
	SGE_RENDERER_SYMBOL
	parameters(
		sge::renderer::state::ffp::lighting::diffuse_color const &diffuse,
		sge::renderer::state::ffp::lighting::ambient_color const &ambient,
		sge::renderer::state::ffp::lighting::specular_color const &specular,
		sge::renderer::state::ffp::lighting::material::emissive_color const &emissive,
		sge::renderer::state::ffp::lighting::material::shininess shininess
	);

	/**
	 * \brief Returns the diffuse part
	*/
	SGE_RENDERER_SYMBOL
	sge::renderer::state::ffp::lighting::diffuse_color const &
	diffuse() const;

	/**
	 * \brief Returns the ambient part
	*/
	SGE_RENDERER_SYMBOL
	sge::renderer::state::ffp::lighting::ambient_color const &
	ambient() const;

	/**
	 * \brief Returns the specular part
	*/
	SGE_RENDERER_SYMBOL
	sge::renderer::state::ffp::lighting::specular_color const &
	specular() const;

	/**
	 * \brief Returns the emissive part
	*/
	SGE_RENDERER_SYMBOL
	sge::renderer::state::ffp::lighting::material::emissive_color const &
	emissive() const;

	/**
	 * \brief Returns the shininess
	*/
	SGE_RENDERER_SYMBOL
	sge::renderer::state::ffp::lighting::material::shininess const
	shininess() const;
private:
	sge::renderer::state::ffp::lighting::diffuse_color diffuse_;

	sge::renderer::state::ffp::lighting::ambient_color ambient_;

	sge::renderer::state::ffp::lighting::specular_color specular_;

	sge::renderer::state::ffp::lighting::material::emissive_color emissive_;

	sge::renderer::state::ffp::lighting::material::shininess shininess_;
};

}
}
}
}
}
}

#endif
