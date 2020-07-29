//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/state/core/sampler/context.hpp>
#include <sge/opengl/state/core/sampler/object.hpp>
#include <sge/opengl/texture/render_binding.hpp>
#include <sge/opengl/texture/set_samplers.hpp>
#include <fcppt/make_ref.hpp>


void
sge::opengl::texture::set_samplers(
	sge::opengl::texture::render_binding const &_render_binding,
	sge::opengl::context::object &_context
)
{
	sge::opengl::context::use<
		sge::opengl::state::core::sampler::context
	>(
		fcppt::make_ref(
			_context
		),
		fcppt::make_ref(
			_context
		)
	).get(
		_render_binding.stage()
	).set(
		_render_binding
	);
}
