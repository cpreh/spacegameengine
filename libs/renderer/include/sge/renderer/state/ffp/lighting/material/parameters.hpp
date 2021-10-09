//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_STATE_FFP_LIGHTING_MATERIAL_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_LIGHTING_MATERIAL_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/ffp/lighting/ambient_color.hpp>
#include <sge/renderer/state/ffp/lighting/diffuse_color.hpp>
#include <sge/renderer/state/ffp/lighting/specular_color.hpp>
#include <sge/renderer/state/ffp/lighting/material/emissive_color.hpp>
#include <sge/renderer/state/ffp/lighting/material/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/material/shininess.hpp>

namespace sge::renderer::state::ffp::lighting::material
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
  SGE_RENDERER_DETAIL_SYMBOL
  parameters(
      sge::renderer::state::ffp::lighting::diffuse_color diffuse,
      sge::renderer::state::ffp::lighting::ambient_color ambient,
      sge::renderer::state::ffp::lighting::specular_color specular,
      sge::renderer::state::ffp::lighting::material::emissive_color emissive,
      sge::renderer::state::ffp::lighting::material::shininess shininess);

  [[nodiscard]]
  /**
	 * \brief Returns the diffuse part
	*/
  SGE_RENDERER_DETAIL_SYMBOL sge::renderer::state::ffp::lighting::diffuse_color const &
  diffuse() const;

  [[nodiscard]]
  /**
	 * \brief Returns the ambient part
	*/
  SGE_RENDERER_DETAIL_SYMBOL sge::renderer::state::ffp::lighting::ambient_color const &
  ambient() const;

  [[nodiscard]]
  /**
	 * \brief Returns the specular part
	*/
  SGE_RENDERER_DETAIL_SYMBOL sge::renderer::state::ffp::lighting::specular_color const &
  specular() const;

  [[nodiscard]]
  /**
	 * \brief Returns the emissive part
	*/
  SGE_RENDERER_DETAIL_SYMBOL sge::renderer::state::ffp::lighting::material::emissive_color const &
  emissive() const;

  [[nodiscard]]
  /**
	 * \brief Returns the shininess
	*/
  SGE_RENDERER_DETAIL_SYMBOL sge::renderer::state::ffp::lighting::material::shininess
  shininess() const;

private:
  sge::renderer::state::ffp::lighting::diffuse_color diffuse_;

  sge::renderer::state::ffp::lighting::ambient_color ambient_;

  sge::renderer::state::ffp::lighting::specular_color specular_;

  sge::renderer::state::ffp::lighting::material::emissive_color emissive_;

  sge::renderer::state::ffp::lighting::material::shininess shininess_;
};

}

#endif
