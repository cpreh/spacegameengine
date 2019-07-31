//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/call_fun_ref.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/fbo/attach_texture_2d.hpp>
#include <sge/opengl/fbo/attachment_type.hpp>
#include <sge/opengl/fbo/config.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/opengl/texture/id.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/to_signed.hpp>


void
sge::opengl::fbo::attach_texture_2d(
	sge::opengl::fbo::config const &_context,
	sge::opengl::fbo::attachment_type const _attachment,
	sge::opengl::texture::buffer_type const _texture_type,
	sge::opengl::texture::id const _texture_id,
	sge::renderer::texture::mipmap::level const _level
)
{
	sge::opengl::call_fun_ref(
		_context.framebuffer_texture_2d(),
		_context.framebuffer_target(),
		_attachment.get(),
		_texture_type.get(),
		_texture_id.get(),
		fcppt::cast::to_signed(
			_level.get()
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("Binding a texture to an fbo failed."),
		sge::renderer::exception
	)
}
