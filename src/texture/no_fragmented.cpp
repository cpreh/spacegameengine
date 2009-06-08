/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/texture/no_fragmented.hpp>
#include <sge/texture/guaranteed_free.hpp>
#include <sge/texture/part_fragmented.hpp>
#include <sge/texture/atlasing.hpp>
#include <sge/renderer/device.hpp>
#include <sge/math/dim/output.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/rect/basic_impl.hpp>
#include <sge/log/headers.hpp>
#include <sge/text.hpp>
#include <sge/make_shared_ptr.hpp>
#include <boost/ref.hpp>
#include <ostream>

sge::texture::no_fragmented::no_fragmented(
	renderer::device_ptr const rend,
	image::color::format::type const format,
	renderer::filter::texture const &filter)
 :
 	rend(rend),
	format(format),
 	filter(filter)
{}

sge::texture::part_ptr const
sge::texture::no_fragmented::consume_fragment(
	renderer::dim_type const &dim)
{
	if(tex)
		return part_ptr();

	renderer::dim_type const real_dim(
		atlased_bounds(
			dim
		)
	);

	tex = rend->create_texture(
		real_dim,
		format,
		filter,
		renderer::resource_flags::none
	);

	if(real_dim != dim)
		SGE_LOG_WARNING(
			log::global(),
			log::_1
				<< SGE_TEXT("You used a texture::no_fragmented whose dimensions are not a power of 2.")\
				SGE_TEXT(" This is slower to load and requires more texture memory because it needs atlasing and thus is not intuitive.")\
				SGE_TEXT(" The texture's size was ")
				<< dim
				<< SGE_TEXT('.')
		);

	return part_ptr(
		make_shared_ptr<
			part_fragmented
		>(
			renderer::lock_rect(
				renderer::lock_rect::point_type::null(),
				atlased_size(dim)
			),
			boost::ref(*this),
			need_atlasing(dim.w()),
			need_atlasing(dim.h())
		)
	);
}

void
sge::texture::no_fragmented::on_return_fragment(
	part const &)
{
	tex.reset();
}

sge::renderer::texture_ptr const
sge::texture::no_fragmented::texture() const
{
	return tex;
}

bool sge::texture::no_fragmented::repeatable() const
{
	return true;
}

sge::texture::free_type
sge::texture::no_fragmented::free_value() const
{
	return empty() ? 0 : guaranteed_free();
}

bool
sge::texture::no_fragmented::empty() const
{
	return !tex;
}
