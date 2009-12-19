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


#include <fcppt/texture/no_fragmented.hpp>
#include <fcppt/texture/guaranteed_free.hpp>
#include <fcppt/texture/part_fragmented.hpp>
#include <fcppt/texture/atlasing.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <sge/log/headers.hpp>
#include <sge/log/global.hpp>
#include <fcppt/text.hpp>
#include <sge/make_shared_ptr.hpp>
#include <tr1/functional>
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
			log::_
				<< FCPPT_TEXT("You used a texture::no_fragmented whose dimensions are not a power of 2.")\
				FCPPT_TEXT(" This is slower to load and requires more texture memory because it needs atlasing and thus is not intuitive.")\
				FCPPT_TEXT(" The texture's size was ")
				<< dim
				<< FCPPT_TEXT('.')
		);

	return part_ptr(
		make_shared_ptr<
			part_fragmented
		>(
			renderer::lock_rect(
				renderer::lock_rect::pos_type::null(),
				atlased_size(dim)
			),
			std::tr1::ref(
				*this
			),
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
