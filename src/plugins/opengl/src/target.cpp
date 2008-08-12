/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../common.hpp"
#include "../target.hpp"
#include "../framebuffer_functions.hpp"
#include <sge/renderer/scoped_lock.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/exception.hpp>
#include <sge/string.hpp>
#include <boost/gil/extension/dynamic_image/apply_operation.hpp>

void sge::ogl::target::lock()
{
	renderer::lock_rect const dest(
		renderer::lock_rect::point_type(0, 0),
		dim());
	lock(dest);
}

void sge::ogl::target::lock(
	renderer::lock_rect const &dest)
{
	if(buffer)
		throw exception(
			SGE_TEXT("renderer::target()::lock(): already locked!"));

	buffer.reset(
		new pixel_pack_buffer(
			dest.dim().content(),
			stride(),
			renderer::resource_flags::none,
			0));
	bind_me();

	buffer->lock(
		renderer::lock_flags::readonly);

	read_pixels(
		dest.left(),
		dest.top(),
		dest.dim().w(),
		dest.dim().h(),
		format(),
		format_type(),
		buffer->data());
}

void sge::ogl::target::unlock()
{
	buffer->unlock();
	buffer.reset();
}

sge::renderer::const_image_view const
sge::ogl::target::view() const
{
	return renderer::const_image_view(
		boost::gil::rgba8_view_t(
			boost::gil::interleaved_view(
				dim().w(),
				dim().h(),
				reinterpret_cast<renderer::rgba8_pixel *>( // FIXME: why can't we use const * here?
					buffer->data()),
				dim().w() * stride())));
}
