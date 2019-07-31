//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/state/core/set_defaults.hpp>
#include <sge/opengl/state/core/blend/set.hpp>
#include <sge/opengl/state/core/depth_stencil/set.hpp>
#include <sge/opengl/state/core/rasterizer/set.hpp>
#include <sge/opengl/state/core/sampler/set_defaults.hpp>
#include <sge/renderer/state/core/blend/const_optional_object_ref.hpp>
#include <sge/renderer/state/core/depth_stencil/const_optional_object_ref.hpp>
#include <sge/renderer/state/core/rasterizer/const_optional_object_ref.hpp>


void
sge::opengl::state::core::set_defaults(
	sge::opengl::context::object &_context
)
{
	sge::opengl::state::core::blend::set(
		_context,
		sge::renderer::state::core::blend::const_optional_object_ref()
	);

	sge::opengl::state::core::depth_stencil::set(
		_context,
		sge::renderer::state::core::depth_stencil::const_optional_object_ref()
	);

	sge::opengl::state::core::rasterizer::set(
		_context,
		sge::renderer::state::core::rasterizer::const_optional_object_ref()
	);

	sge::opengl::state::core::sampler::set_defaults(
		_context
	);
}
