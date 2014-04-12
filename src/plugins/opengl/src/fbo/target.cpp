/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/basic_target_impl.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/context/device/object_fwd.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/fbo/attachment.hpp>
#include <sge/opengl/fbo/attachment_type.hpp>
#include <sge/opengl/fbo/attachment_unique_ptr.hpp>
#include <sge/opengl/fbo/context.hpp>
#include <sge/opengl/fbo/depth_stencil_format_to_attachment.hpp>
#include <sge/opengl/fbo/depth_stencil_surface.hpp>
#include <sge/opengl/fbo/error_string_map.hpp>
#include <sge/opengl/fbo/last_context.hpp>
#include <sge/opengl/fbo/no_buffer.hpp>
#include <sge/opengl/fbo/optional_attachment_type.hpp>
#include <sge/opengl/fbo/render_buffer_binding.hpp>
#include <sge/opengl/fbo/target.hpp>
#include <sge/opengl/fbo/temporary_bind.hpp>
#include <sge/opengl/fbo/texture_binding.hpp>
#include <sge/opengl/fbo/unbind.hpp>
#include <sge/opengl/texture/buffer_base.hpp>
#include <sge/opengl/texture/color_surface.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/color_buffer/optional_surface_ref.hpp>
#include <sge/renderer/depth_stencil_buffer/optional_surface_ref.hpp>
#include <sge/renderer/target/offscreen.hpp>
#include <sge/renderer/target/surface_index.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <fcppt/format.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::opengl::fbo::target::target(
	sge::opengl::context::system::object &_system_context,
	sge::opengl::context::device::object &_device_context
)
:
	base(
		_device_context,
		sge::renderer::target::viewport(
			sge::renderer::pixel_rect::null()
		)
	),
	context_(
		opengl::context::use<
			sge::opengl::fbo::context
		>(
			_system_context
		)
	),
	last_context_(
		sge::opengl::context::use<
			sge::opengl::fbo::last_context
		>(
			_device_context
		)
	),
	fbo_(
		context_
	),
	height_(),
	color_attachments_(),
	depth_stencil_attachment_()
{
}

sge::opengl::fbo::target::~target()
{
	opengl::fbo::temporary_bind const scoped_exit(
		context_,
		last_context_,
		fbo_
	);

	depth_stencil_attachment_.reset();

	color_attachments_.clear();
}

void
sge::opengl::fbo::target::on_bind()
{
	fbo_.bind();

	last_context_.last_buffer(
		fbo_.id()
	);
}

void
sge::opengl::fbo::target::on_unbind()
{
	sge::opengl::fbo::unbind(
		context_
	);

	last_context_.last_buffer(
		sge::opengl::fbo::no_buffer()
	);
}

void
sge::opengl::fbo::target::end_rendering()
{
}

void
sge::opengl::fbo::target::color_surface(
	sge::renderer::color_buffer::optional_surface_ref const &_surface,
	sge::renderer::target::surface_index const _index
)
{
	sge::opengl::fbo::temporary_bind const scoped_exit(
		context_,
		last_context_,
		fbo_
	);

	color_attachments_.erase(
		_index
	);

	if(
		_index.get() == 0u
	)
		height_ =
			_surface
			?
				optional_screen_unit(
					static_cast<
						sge::renderer::screen_unit
					>(
						_surface->size().h()
					)
				)
			:
				optional_screen_unit()
			;

	if(
		_surface
	)
	{
		sge::opengl::texture::color_surface &texture_surface(
			dynamic_cast<
				sge::opengl::texture::color_surface &
			>(
				*_surface
			)
		);

		if(
			!texture_surface.is_render_target().get()
		)
			throw sge::renderer::exception(
				FCPPT_TEXT("You tried to use a texture as a render target ")
				FCPPT_TEXT("which hasn't been created as such!")
			);

		fcppt::container::ptr::insert_unique_ptr_map(
			color_attachments_,
			_index,
			this->create_texture_binding(
				texture_surface,
				sge::opengl::fbo::attachment_type(
					context_.color_attachment().get()
					+ _index.get()
				)
			)
		);
	}
}

void
sge::opengl::fbo::target::depth_stencil_surface(
	sge::renderer::depth_stencil_buffer::optional_surface_ref const &_surface
)
{
	sge::opengl::fbo::temporary_bind const scoped_exit(
		context_,
		last_context_,
		fbo_
	);

	depth_stencil_attachment_.reset();

	if(
		!_surface
	)
		return;

	sge::opengl::fbo::optional_attachment_type const attachment(
		sge::opengl::fbo::depth_stencil_format_to_attachment(
			context_,
			_surface->format()
		)
	);

	if(
		!attachment
	)
		throw sge::renderer::unsupported(
			FCPPT_TEXT("depth_stencil_surface target attachment!"),
			FCPPT_TEXT("3.0"),
			FCPPT_TEXT("")
		);

	if(
		sge::opengl::fbo::depth_stencil_surface *ptr =
			dynamic_cast<
				sge::opengl::fbo::depth_stencil_surface *
			>(
				&*_surface
			)
	)
	{
		depth_stencil_attachment_ =
			this->create_buffer_binding(
				ptr->render_buffer(),
				*attachment
			);

		return;
	}

	if(
		sge::opengl::texture::buffer_base *ptr =
			dynamic_cast<
				sge::opengl::texture::buffer_base *
			>(
				&*_surface
			)
	)
	{
		depth_stencil_attachment_ =
			this->create_texture_binding(
				*ptr,
				*attachment
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
		height_
		?
			*height_
		:
			0u;
}

sge::opengl::fbo::attachment_unique_ptr
sge::opengl::fbo::target::create_texture_binding(
	sge::opengl::texture::buffer_base &_surface,
	sge::opengl::fbo::attachment_type const _attachment
)
{
	attachment_unique_ptr ret(
		fcppt::make_unique_ptr<
			sge::opengl::fbo::texture_binding
		>(
			context_,
			_surface,
			_attachment
		)
	);

	this->check();

	return
		std::move(
			ret
		);
}

sge::opengl::fbo::attachment_unique_ptr
sge::opengl::fbo::target::create_buffer_binding(
	sge::opengl::fbo::render_buffer const &_buffer,
	sge::opengl::fbo::attachment_type const _attachment
)
{
	attachment_unique_ptr ret(
		fcppt::make_unique_ptr<
			sge::opengl::fbo::render_buffer_binding
		>(
			context_,
			_buffer,
			_attachment
		)
	);

	this->check();

	return
		std::move(
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
		status
		!=
		context_.framebuffer_complete()
	)
	{
		sge::opengl::fbo::error_string_map const &error_strings(
			context_.error_strings()
		);

		sge::opengl::fbo::error_string_map::const_iterator const it(
			error_strings.find(
				status
			)
		);

		throw sge::renderer::exception(
			FCPPT_TEXT("FBO is incomplete! ")
			+
			(
				it == error_strings.end()
				?
					FCPPT_TEXT("unknown")
				:
					it->second
			)
		);
	}
}

template class
sge::opengl::basic_target<
	sge::renderer::target::offscreen
>;
