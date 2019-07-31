//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/fbo/attach_texture_2d.hpp>
#include <sge/opengl/fbo/attachment_type.hpp>
#include <sge/opengl/fbo/config_fwd.hpp>
#include <sge/opengl/fbo/texture_binding.hpp>
#include <sge/opengl/texture/buffer_base.hpp>
#include <sge/opengl/texture/id.hpp>


sge::opengl::fbo::texture_binding::texture_binding(
	sge::opengl::fbo::config const &_context,
	sge::opengl::texture::buffer_base &_buffer,
	sge::opengl::fbo::attachment_type const _attachment
)
:
	context_(
		_context
	),
	buffer_(
		_buffer
	),
	attachment_(
		_attachment
	)
{
	sge::opengl::fbo::attach_texture_2d(
		_context,
		_attachment,
		_buffer.buffer_type(),
		_buffer.id(),
		_buffer.level()
	);
}

sge::opengl::fbo::texture_binding::~texture_binding()
{
	sge::opengl::fbo::attach_texture_2d(
		context_,
		attachment_,
		buffer_.buffer_type(),
		sge::opengl::texture::id(
			0u
		),
		buffer_.level()
	);
}
