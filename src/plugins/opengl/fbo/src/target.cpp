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


#include "../target.hpp"
#include "../bind.hpp"
#include "../context.hpp"
#include "../init_viewport.hpp"
#include "../render_buffer.hpp"
#include "../render_buffer_binding.hpp"
#include "../scoped_unbind.hpp"
#include "../../check_state.hpp"
#include "../../depth_stencil_texture.hpp"
#include "../../texture.hpp"
#include "../../context/use.hpp"
#include <sge/renderer/exception.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/pixel_pos.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/renderer/viewport.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/text.hpp>

sge::opengl::fbo::target::target(
	sge::opengl::context::object &_context,
	sge::renderer::parameters const &_param,
	opengl::texture_ptr const _texture,
	opengl::depth_stencil_texture_ptr const _depth_stencil_texture
)
:
	opengl::target(
		fbo::init_viewport(
			_texture,
			_depth_stencil_texture
		)
	),
	context_(
		opengl::context::use<
			fbo::context
		>(
			_context
		)
	),
	texture_(
		_texture
	),
	dim_(
		texture_
		?
			texture_->dim()
		:
			dim_type::null()
	),
	fbo_(
		context_
	)
{
	// important: to bind buffers to an fbo
	// it must be bound itself
	// but this has to be undone after this function!
	opengl::fbo::scoped_unbind const scoped_exit(
		context_
	);

	if(
		_texture
	)
		add_texture_binding(
			_texture,
			context_.color_attachment()
		);

	if(
		_depth_stencil_texture
	)
		add_texture_binding(
			_depth_stencil_texture,
			context_.depth_attachment()
		);
	else if(
		_param.depth_buffer() != renderer::depth_buffer::off
	)
		attach_buffer(
			GL_DEPTH_COMPONENT,
			context_.depth_attachment()
		);
	
	if(
		_param.stencil_buffer() != renderer::stencil_buffer::off
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
}

sge::opengl::fbo::target::~target()
{
}

void
sge::opengl::fbo::target::bind() const
{
	fbo_.bind();

	context_.last_buffer(
		fbo_.id()
	);
}

void
sge::opengl::fbo::target::unbind() const
{
	opengl::fbo::bind(
		context_,
		0
	);

	context_.last_buffer(
		0
	);
}

sge::image::view::const_object const
sge::opengl::fbo::target::lock(
	renderer::lock_rect const &_dest
) const
{
	return
		texture_->lock(
			_dest
		);
}

void
sge::opengl::fbo::target::unlock() const
{
	texture_->unlock();
}

sge::renderer::target::dim_type const
sge::opengl::fbo::target::dim() const
{
	return dim_;
}

void
sge::opengl::fbo::target::add_texture_binding(
	opengl::texture_base_ptr const _texture,
	GLenum const _type
)
{
	fcppt::container::ptr::push_back_unique_ptr(
		texture_bindings_,
		fcppt::make_unique_ptr<
			opengl::fbo::texture_binding
		>(
			std::tr1::ref(
				context_
			),
			_texture,
			std::tr1::ref(
				fbo_
			),
			_type
		)
	);
}

void
sge::opengl::fbo::target::attach_buffer(
	GLenum const _component,
	GLenum const _attachment
)
{
	{
		typedef fcppt::unique_ptr<
			render_buffer
		> render_buffer_ptr;

		render_buffer_ptr ptr(
			fcppt::make_unique_ptr<
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

		fcppt::container::ptr::push_back_unique_ptr(
			render_buffers_,
			move(
				ptr
			)
		);
	}

	typedef fcppt::unique_ptr<
		render_buffer_binding
	> render_buffer_binding_ptr;

	render_buffer_binding_ptr ptr(
		fcppt::make_unique_ptr<
			fbo::render_buffer_binding
		>(
			context_,
			fbo_,
			render_buffers_.back(),
			_attachment
		)
	);

	fcppt::container::ptr::push_back_unique_ptr(
		render_buffer_bindings_,
		move(
			ptr
		)
	);
}
