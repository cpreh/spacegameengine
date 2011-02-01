/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include "../render_buffer.hpp"
#include "../render_buffer_binding.hpp"
#include "../scoped_unbind.hpp"
#include "../texture_binding.hpp"
#include "../../check_state.hpp"
#include "../../depth_stencil_texture.hpp"
#include "../../texture_surface.hpp"
#include "../../context/use.hpp"
#include <sge/renderer/exception.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/renderer/viewport.hpp>
#include <fcppt/algorithm/ptr_container_erase_if.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/dynamic_pointer_cast.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <boost/spirit/home/phoenix/bind/bind_member_function.hpp>
#include <boost/spirit/home/phoenix/core/argument.hpp>
#include <boost/spirit/home/phoenix/operator/comparison.hpp>

sge::opengl::fbo::target::target(
	sge::opengl::context::object &_context
)
:
	opengl::target(
		sge::renderer::viewport(
			sge::renderer::pixel_rect::null()
		)
	),
	context_(
		opengl::context::use<
			fbo::context
		>(
			_context
		)
	),
	fbo_(
		context_
	)
{
#if 0
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
#endif
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

void
sge::opengl::fbo::target::add_surface(
	renderer::color_surface_ptr const _surface
)
{
	this->add_texture_binding(
		fcppt::dynamic_pointer_cast<
			opengl::texture_surface
		>(
			_surface
		),
		context_.color_attachment()
	);
}

void
sge::opengl::fbo::target::remove_surface(
	renderer::color_surface_ptr const _surface
)
{
	if(
		!fcppt::algorithm::ptr_container_erase_if(
			texture_bindings_,
			boost::phoenix::bind(
				&fbo::texture_binding::surface,
				boost::phoenix::arg_names::arg1
			)
			==
			fcppt::dynamic_pointer_cast<
				opengl::texture_surface
			>(
				_surface
			)
		)
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("fbo::target::remove_surface(): Invalid surface!")
		);
}

void
sge::opengl::fbo::target::add_surface(
	renderer::depth_stencil_surface_ptr const _surface
)
{
}

void
sge::opengl::fbo::target::remove_surface(
	renderer::depth_stencil_surface_ptr const _surface
)
{
}

sge::renderer::screen_unit
sge::opengl::fbo::target::height() const
{
}

void
sge::opengl::fbo::target::add_texture_binding(
	opengl::texture_surface_base_ptr const _surface,
	GLenum const _attachment
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
			_surface,
			std::tr1::ref(
				fbo_
			),
			_attachment
		)
	);
}

void
sge::opengl::fbo::target::attach_buffer(
	GLenum const _component,
	GLenum const _attachment
)
{
#if 0
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
#endif
}
