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


#include "../surface.hpp"
#include "../basic_surface_impl.hpp"
#include "../readonly_lock.hpp"
#include "../scoped_work_bind.hpp"
#include "../funcs/get_image.hpp"
#include "../../convert/format_to_color.hpp"
#include <sge/image/color/format_stride.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/image2d/view/optional_pitch.hpp>
#include <sge/image2d/view/sub.hpp>
#include <sge/renderer/color_surface.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/ref.hpp>


sge::opengl::texture::surface::surface(
	texture::scoped_work_bind const &_binding,
	opengl::context::object &_context,
	texture::type const _type,
	texture::id const _id,
	renderer::stage const _stage,
	renderer::resource_flags_field const &_resource_flags,
	opengl::color_format const _color_format,
	opengl::color_format_type const _color_format_type,
	bool const _is_render_target
)
:
	base(
		_binding,
		_type,
		_id,
		_stage
	),
	context_(_context),
	stage_(_stage),
	resource_flags_(_resource_flags),
	color_format_(
		_color_format
	),
	color_format_type_(
		_color_format_type
	),
	is_render_target_(_is_render_target),
	lock_()
{
}

sge::opengl::texture::surface::~surface()
{
}

bool
sge::opengl::texture::surface::is_render_target() const
{
	return is_render_target_;
}

sge::opengl::texture::surface::const_view const
sge::opengl::texture::surface::lock(
	rect const &_lock_rect
) const
{
	sge::image::color::format::type const image_color_format(
		opengl::convert::format_to_color(
			color_format_,
			color_format_type_
		)
	);

	lock_.take(
		fcppt::make_unique_ptr<
			opengl::texture::readonly_lock
		>(
			fcppt::ref(
				context_
			),
			this->size().content(),
			image::color::format_stride(
				image_color_format
			),
			resource_flags_
		)
	);

	{
		opengl::texture::scoped_work_bind const binding(
			context_,
			this->type(),
			this->id(),
			stage_
		);

		texture::funcs::get_image(
			binding,
			this->type(),
			color_format_,
			color_format_type_,
			lock_->read_pointer(),
			stage_
		);
	}

	lock_->lock();

	return
		sge::image2d::view::sub(
			sge::image2d::view::make_const(
				lock_->read_view_pointer(),
				this->size(),
				image_color_format,
				image2d::view::optional_pitch()
			),
			_lock_rect
		);
}

void
sge::opengl::texture::surface::unlock() const
{
	lock_->unlock();

	lock_.reset();
}

template class
sge::opengl::texture::basic_surface<
	sge::renderer::color_surface
>;
