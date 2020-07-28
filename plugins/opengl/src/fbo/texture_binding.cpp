//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/fbo/attach_texture_2d.hpp>
#include <sge/opengl/fbo/attachment_type.hpp>
#include <sge/opengl/fbo/const_config_ref.hpp>
#include <sge/opengl/fbo/texture_binding.hpp>
#include <sge/opengl/texture/buffer_base.hpp>
#include <sge/opengl/texture/buffer_base_ref.hpp>
#include <sge/opengl/texture/id.hpp>


sge::opengl::fbo::texture_binding::texture_binding(
	sge::opengl::fbo::const_config_ref const _context,
	sge::opengl::texture::buffer_base_ref const _buffer,
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
		_context.get(),
		_attachment,
		_buffer.get().buffer_type(),
		_buffer.get().id(),
		_buffer.get().level()
	);
}

sge::opengl::fbo::texture_binding::~texture_binding()
{
	sge::opengl::fbo::attach_texture_2d(
		context_.get(),
		attachment_,
		buffer_.get().buffer_type(),
		sge::opengl::texture::id(
			0U
		),
		buffer_.get().level()
	);
}
