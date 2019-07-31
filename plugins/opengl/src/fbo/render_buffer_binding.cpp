//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/fbo/attach_render_buffer.hpp>
#include <sge/opengl/fbo/attachment_type.hpp>
#include <sge/opengl/fbo/config_fwd.hpp>
#include <sge/opengl/fbo/render_buffer.hpp>
#include <sge/opengl/fbo/render_buffer_binding.hpp>


sge::opengl::fbo::render_buffer_binding::render_buffer_binding(
	sge::opengl::fbo::config const &_context,
	sge::opengl::fbo::render_buffer const &_render_buffer,
	sge::opengl::fbo::attachment_type const _what
)
:
	context_(
		_context
	),
	what_(
		_what
	)
{
	sge::opengl::fbo::attach_render_buffer(
		_context,
		_what,
		_render_buffer.id()
	);
}

sge::opengl::fbo::render_buffer_binding::~render_buffer_binding()
{
	sge::opengl::fbo::attach_render_buffer(
		context_,
		what_,
		0
	);
}
