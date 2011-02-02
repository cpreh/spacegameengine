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
#include "../attachment.hpp"
#include "../bind.hpp"
#include "../context.hpp"
#include "../depth_stencil_surface_ptr.hpp"
#include "../depth_stencil_surface.hpp"
#include "../render_buffer_binding.hpp"
#include "../temporary_bind.hpp"
#include "../texture_binding.hpp"
#include "../../basic_target_impl.hpp"
#include "../../check_state.hpp"
#include "../../texture_surface.hpp"
#include "../../context/use.hpp"
#include <sge/renderer/exception.hpp>
#include <sge/renderer/target.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/viewport.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/dynamic_pointer_cast.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/text.hpp>

sge::opengl::fbo::target::target(
	sge::opengl::context::object &_context
)
:
	base(
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
	),
	color_attachments_(),
	depth_stencil_attachment_()
{
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
sge::opengl::fbo::target::color_surface(
	renderer::color_surface_ptr const _surface,
	renderer::surface_index const _index
)
{
	color_attachments_.erase(
		_index
	);

	if(
		_surface
	)
		fcppt::container::ptr::insert_unique_ptr_map(
			color_attachments_,
			_index,
			this->create_texture_binding(
				fcppt::dynamic_pointer_cast<
					opengl::texture_surface
				>(
					_surface
				),
				context_.color_attachment()
				+ _index.get()
			)
		);
}

void
sge::opengl::fbo::target::depth_stencil_surface(
	renderer::depth_stencil_surface_ptr const _surface
)
{
	if(
		context_.depth_stencil_attachment()
		== 0
	)
		throw sge::renderer::unsupported(
			FCPPT_TEXT("depth_stencil_surface target attachment!"),
			FCPPT_TEXT("3.0"),
			FCPPT_TEXT("")
		);

	if(
		!_surface
	)
	{
		depth_stencil_attachment_.reset();

		return;
	}

	if(
		opengl::fbo::depth_stencil_surface_ptr const ptr =
			fcppt::dynamic_pointer_cast<
				opengl::fbo::depth_stencil_surface
			>(
				_surface
			)
	)
	{
		depth_stencil_attachment_.take(
			this->create_buffer_binding(
				ptr->render_buffer(),
				context_.depth_stencil_attachment()
			)
		);

		return;
	}

	if(
		opengl::texture_surface_base_ptr const ptr =
			fcppt::dynamic_pointer_cast<
				opengl::texture_surface_base
			>(
				_surface
			)
	)
	{
		depth_stencil_attachment_.take(
			this->create_texture_binding(
				ptr,
				context_.depth_stencil_attachment()
			)
		);

		return;
	}

	throw sge::renderer::exception(
		FCPPT_TEXT("Invalid depth_stencil_surface in add_surface!")
	);
}

sge::renderer::screen_unit
sge::opengl::fbo::target::height() const
{
	return
		static_cast<
			renderer::screen_unit
		>(
			this->viewport().get().h()
		);
}

sge::opengl::fbo::attachment_unique_ptr
sge::opengl::fbo::target::create_texture_binding(
	opengl::texture_surface_base_ptr const _surface,
	GLenum const _attachment
)
{
	opengl::fbo::temporary_bind const scoped_exit(
		context_,
		fbo_
	);

	attachment_unique_ptr ret(
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

	this->check();

	return
		move(
			ret
		);
}

sge::opengl::fbo::attachment_unique_ptr
sge::opengl::fbo::target::create_buffer_binding(
	fbo::render_buffer const &_buffer,
	GLenum const _attachment
)
{
	opengl::fbo::temporary_bind const scoped_exit(
		context_,
		fbo_
	);

	attachment_unique_ptr ret(
		fcppt::make_unique_ptr<
			fbo::render_buffer_binding
		>(
			std::tr1::ref(
				context_
			),
			std::tr1::ref(
				fbo_
			),
			_buffer,
			_attachment
		)
	);

	this->check();

	return
		move(
			ret
		);
}

void
sge::opengl::fbo::target::check()
{
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

template class
sge::opengl::basic_target<
	sge::renderer::target
>;
