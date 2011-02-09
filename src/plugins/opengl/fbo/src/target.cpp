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
#include "../depth_stencil_format_to_attachment.hpp"
#include "../depth_stencil_surface_ptr.hpp"
#include "../depth_stencil_surface.hpp"
#include "../render_buffer_binding.hpp"
#include "../temporary_bind.hpp"
#include "../texture_binding.hpp"
#include "../../basic_target_impl.hpp"
#include "../../check_state.hpp"
#include "../../context/use.hpp"
#include "../../texture/surface.hpp"
#include <sge/renderer/exception.hpp>
#include <sge/renderer/target.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/viewport.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/dynamic_pointer_cast.hpp>
#include <fcppt/format.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
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
	depth_stencil_attachment_(),
	dim_()
{
}

sge::opengl::fbo::target::~target()
{
	opengl::fbo::temporary_bind const scoped_exit(
		context_,
		fbo_
	);

	depth_stencil_attachment_.reset();

	color_attachments_.clear();
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
	opengl::fbo::temporary_bind const scoped_exit(
		context_,
		fbo_
	);

	color_attachments_.erase(
		_index
	);

	this->remove_dim();

	if(
		_surface
	)
	{
		this->add_dim(
			_surface->dim()
		);

		fcppt::container::ptr::insert_unique_ptr_map(
			color_attachments_,
			_index,
			this->create_texture_binding(
				fcppt::dynamic_pointer_cast<
					opengl::texture::surface
				>(
					_surface
				),
				context_.color_attachment()
				+ _index.get()
			)
		);
	}
}

void
sge::opengl::fbo::target::depth_stencil_surface(
	renderer::depth_stencil_surface_ptr const _surface
)
{
	GLenum const attachment(
		fbo::depth_stencil_format_to_attachment(
			context_,
			_surface->format()
		)
	);

	if(
		attachment
		== 0
	)
		throw sge::renderer::unsupported(
			FCPPT_TEXT("depth_stencil_surface target attachment!"),
			FCPPT_TEXT("3.0"),
			FCPPT_TEXT("")
		);
	
	opengl::fbo::temporary_bind const scoped_exit(
		context_,
		fbo_
	);

	depth_stencil_attachment_.reset();

	this->remove_dim();

	if(
		!_surface
	)
		return;

	this->add_dim(
		_surface->dim()
	);

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
				attachment
			)
		);

		return;
	}

	if(
		opengl::texture::surface_base_ptr const ptr =
			fcppt::dynamic_pointer_cast<
				opengl::texture::surface_base
			>(
				_surface
			)
	)
	{
		depth_stencil_attachment_.take(
			this->create_texture_binding(
				ptr,
				attachment
			)
		);

		return;
	}

	throw sge::renderer::exception(
		FCPPT_TEXT("Invalid depth_stencil_surface in add_surface!")
	);
}

sge::renderer::optional_dim2 const
sge::opengl::fbo::target::dim() const
{
	return dim_;
}

sge::renderer::screen_unit
sge::opengl::fbo::target::height() const
{
	return
		dim_
		?
			static_cast<
				renderer::screen_unit
			>(
				dim_->h()
			)
		:
			0u;
}

sge::opengl::fbo::attachment_unique_ptr
sge::opengl::fbo::target::create_texture_binding(
	opengl::texture::surface_base_ptr const _surface,
	GLenum const _attachment
)
{
	attachment_unique_ptr ret(
		fcppt::make_unique_ptr<
			opengl::fbo::texture_binding
		>(
			std::tr1::ref(
				context_
			),
			_surface,
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
	attachment_unique_ptr ret(
		fcppt::make_unique_ptr<
			fbo::render_buffer_binding
		>(
			std::tr1::ref(
				context_
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
sge::opengl::fbo::target::add_dim(
	sge::renderer::dim2 const &_dim
)
{
	if(
		!dim_
	)
		dim_ = _dim;
	else if(
		*dim_ != _dim
	)
		throw sge::renderer::exception(
			(
				fcppt::format(
					FCPPT_TEXT("Current target dimension %1% is different ")
					FCPPT_TEXT("from the new surface dimension %2%!")
				)
				%
				*dim_
				%
				_dim
			).str()
		);
}

void
sge::opengl::fbo::target::remove_dim()
{
	if(
		color_attachments_.empty()
		&& !depth_stencil_attachment_
	)
		dim_.reset();
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
