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
#include <sge/renderer/color_surface.hpp>

sge::opengl::texture::surface::surface(
	texture::scoped_work_bind const &_binding,
	texture::type const _type,
	texture::id const _id,
	renderer::stage_type const _stage
)
:
	base(
		_binding,
		_type,
		_id,
		_stage
	)
{
}
	
sge::opengl::texture::surface::~surface()
{
}

sge::image2d::view::const_object const
sge::opengl::texture::surface::lock(
	rect_type const &_rect
) const
{
#if 0
	lock_.reset(
		fcppt::make_unique_ptr<
			opengl::readonly_texture_lock
		>(
			context_,
			dim().content(),
			stride_,
			flags_
		)
	);

	lock_->lock();

	texfuncs::get_image(
		type_,
		format_,
		format_type_,
		lock_->read_pointer(),
		stage_
	);

	lock_->pre_unlock();

	return
		sge::image::view::sub(
			sge::image2d::view::make(
				lock_->read_view_pointer(),
				dim(),
				sge_format_,
				image2d::view::optional_pitch()
			),
			lock_area_
		);
#endif
	return sge::image2d::view::const_object(); // FIXME!
}

void
sge::opengl::texture::surface::unlock() const
{
#if 0
	lock_->unlock();

	lock_.reset();
#endif
}

template class
sge::opengl::texture::basic_surface<
	sge::renderer::color_surface
>;
