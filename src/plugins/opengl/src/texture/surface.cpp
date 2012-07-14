/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image/color/format.hpp>
#include <sge/image/color/format_stride.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/image2d/view/optional_pitch.hpp>
#include <sge/image2d/view/sub.hpp>
#include <sge/opengl/color_format.hpp>
#include <sge/opengl/color_format_type.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/texture/basic_surface_impl.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/id.hpp>
#include <sge/opengl/texture/readonly_lock.hpp>
#include <sge/opengl/texture/scoped_work_binding.hpp>
#include <sge/opengl/texture/surface.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/opengl/texture/funcs/get_image.hpp>
#include <sge/renderer/color_surface.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/ref.hpp>


sge::opengl::texture::surface::surface(
	sge::opengl::texture::binding const &_binding,
	sge::opengl::context::system::object &_system_context,
	sge::opengl::texture::type const _type,
	sge::opengl::texture::id const _id,
	sge::renderer::texture::mipmap::level const _level,
	sge::renderer::resource_flags_field const &_resource_flags,
	sge::image::color::format::type const _format,
	sge::opengl::color_format const _color_format,
	sge::opengl::color_format_type const _color_format_type,
	bool const _is_render_target
)
:
	base(
		_binding,
		_type,
		_id,
		_level
	),
	system_context_(
		_system_context
	),
	resource_flags_(
		_resource_flags
	),
	format_(
		_format
	),
	color_format_(
		_color_format
	),
	color_format_type_(
		_color_format_type
	),
	is_render_target_(
		_is_render_target
	),
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
	lock_.take(
		fcppt::make_unique_ptr<
			opengl::texture::readonly_lock
		>(
			fcppt::ref(
				system_context_
			),
			this->size().content(),
			sge::image::color::format_stride(
				format_
			),
			resource_flags_
		)
	);

	{
		sge::opengl::texture::scoped_work_binding const binding(
			system_context_,
			this->type(),
			this->id()
		);

		sge::opengl::texture::funcs::get_image(
			binding,
			this->type(),
			color_format_,
			color_format_type_,
			lock_->read_pointer(),
			this->level()
		);
	}

	lock_->lock();

	return
		sge::image2d::view::sub(
			sge::image2d::view::make_const(
				lock_->read_view_pointer(),
				this->size(),
				format_,
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
