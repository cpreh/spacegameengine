//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_STATE_FFP_TRANSFORM_MODE_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_TRANSFORM_MODE_HPP_INCLUDED

#include <sge/renderer/state/ffp/transform/mode_fwd.hpp> // IWYU pragma: keep

namespace sge::renderer::state::ffp::transform
{

enum class mode
{
  /**
	\brief The world matrix

	The world matrix describes the transformation of the scene.
	*/
  world,
  /**
	\brief The projection matrix

	The projection matrix describes how the transformed scene is mapped
	onto the screen.
	*/
  projection,
  /**
	\brief The texture matrix

	The texture matrix describes how texture coordinates are transformed.
	*/
  texture,
  /**
	\brief The maximum element
	*/
  fcppt_maximum = texture
};

}

#endif
