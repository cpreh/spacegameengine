//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_CAPS_SYSTEM_HPP_INCLUDED
#define SGE_RENDERER_CAPS_SYSTEM_HPP_INCLUDED

#include <sge/renderer/caps/system_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::renderer::caps
{

/**
\brief Renderer capability flags

\ingroup sge_renderer
*/
enum class system : std::uint8_t
{
  /**
	\brief The renderer is capable of the fixed function pipeline

	The renderer can create fixed function pipeline devices via
	sge::renderer::system::create_ffp_renderer.*/
  ffp,
  /**
	\brief The renderer is capable of OpenGL

	Renderer buffers and textures can be cast to interfaces from
	sge::renderer::opengl.
	*/
  opengl
};

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sge::renderer::caps::system::opengl);

#endif
