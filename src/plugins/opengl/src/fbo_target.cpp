/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include "../fbo_target.hpp"
#include "../bind_fbo.hpp"
#include "../fbo_context.hpp"
#include "../check_state.hpp"
#include "../render_buffer.hpp"
#include "../render_buffer_binding.hpp"
#include "../context/use.hpp"
#include <sge/renderer/texture.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/parameters.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/auto_ptr.hpp>
#include <fcppt/make_auto_ptr.hpp>
#include <fcppt/text.hpp>

sge::opengl::fbo_target::fbo_target(
	sge::opengl::context::object &_context,
	sge::renderer::parameters const &param_,
	opengl::texture_ptr const texture_
)
:
	context_(
		opengl::context::use<
			fbo_context
		>(
			_context
		)
	),
	fbo_(
		context_
	),
	texture_binding_(
		context_,
		texture_,
		fbo_
	)
{
	if(
		param_.depth_buffer() != renderer::depth_buffer::off
	)
		attach_buffer(
			GL_DEPTH_COMPONENT,
			context_.depth_attachment()
		);
	
	if(
		param_.stencil_buffer() != renderer::stencil_buffer::off
	)
		attach_buffer(
			GL_STENCIL_INDEX,
			context_.stencil_attachment()
		);

	GLenum const status(
		context_.check_framebuffer_status()(
			context_.framebuffer_target()
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("Checking the fbo status failed."),
		sge::renderer::exception
	)

	if(
		status !=
		context_.framebuffer_complete()
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("FBO is incomplete!")
		);
	
	// restore the last binding
	opengl::bind_fbo(
		context_,
		context_.last_buffer()
	);
}

sge::opengl::fbo_target::~fbo_target()
{
}

void
sge::opengl::fbo_target::bind() const
{
	fbo_.bind();

	context_.last_buffer(
		fbo_.id()
	);
}

void
sge::opengl::fbo_target::unbind() const
{
	opengl::bind_fbo(
		context_,
		0
	);

	context_.last_buffer(
		0
	);
}

sge::image::view::const_object const
sge::opengl::fbo_target::lock(
	renderer::lock_rect const &_dest
) const
{
	return
		texture_binding_.texture()->lock(
			_dest
		);
}

void
sge::opengl::fbo_target::unlock() const
{
	texture_binding_.texture()->unlock();
}

sge::renderer::target::dim_type const
sge::opengl::fbo_target::dim() const
{
	return texture_binding_.texture()->dim();
}

void
sge::opengl::fbo_target::attach_buffer(
	GLenum const _component,
	GLenum const _attachment
)
{
	{
		typedef fcppt::auto_ptr<
			render_buffer
		> render_buffer_ptr;

		render_buffer_ptr ptr(
			fcppt::make_auto_ptr<
				render_buffer
			>(
				context_
			)
		);

		ptr->store(
			_component,
			static_cast<
				GLsizei
			>(
				dim().w()
			),
			static_cast<
				GLsizei
			>(
				dim().h()
			)
		);

		render_buffers_.push_back(
			ptr
		);
	}

	typedef fcppt::auto_ptr<
		render_buffer_binding
	> render_buffer_binding_ptr;

	render_buffer_binding_ptr ptr(
		fcppt::make_auto_ptr<
			render_buffer_binding
		>(
			context_,
			fbo_,
			render_buffers_.back(),
			_attachment
		)
	);

	render_buffer_bindings_.push_back(
		ptr
	);
}
