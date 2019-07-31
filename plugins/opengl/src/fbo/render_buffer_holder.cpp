//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/common.hpp>
#include <sge/opengl/fbo/config_fwd.hpp>
#include <sge/opengl/fbo/delete_render_buffer.hpp>
#include <sge/opengl/fbo/gen_render_buffer.hpp>
#include <sge/opengl/fbo/render_buffer_holder.hpp>


sge::opengl::fbo::render_buffer_holder::render_buffer_holder(
	sge::opengl::fbo::config const &_context
)
:
	context_(
		_context
	),
	id_(
		sge::opengl::fbo::gen_render_buffer(
			context_
		)
	)
{
}

sge::opengl::fbo::render_buffer_holder::~render_buffer_holder()
{
	sge::opengl::fbo::delete_render_buffer(
		context_,
		id_
	);
}

GLuint
sge::opengl::fbo::render_buffer_holder::id() const
{
	return
		id_;
}
