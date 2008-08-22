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


#include <sge/texture/no_fragmented.hpp>
#include <sge/texture/part_fragmented.hpp>
#include <sge/texture/atlasing.hpp>
#include <sge/iostream.hpp>
#include <sge/math/power.hpp>
#include <sge/log/global.hpp>
#include <sge/log/logger.hpp>
#include <sge/log/temporary_output.hpp>
#include <ostream>

sge::texture::no_fragmented::no_fragmented(
	const renderer::device_ptr rend,
	const renderer::filter_args& my_filter)
 : rend(rend),
   my_filter(my_filter)
{}

const sge::texture::part_ptr
sge::texture::no_fragmented::consume_fragment(
	const renderer::texture::dim_type& dim)
{
	if(tex)
		return part_ptr();

	const renderer::texture::dim_type real_dim(atlased_bounds(dim));

	tex = rend->create_texture(
		real_dim,
		renderer::color_format::rgba8,
		my_filter,
		renderer::resource_flags::none);

	if(real_dim != dim)
		log::global().log(
			log::level::warning,
			log::_1 << SGE_TEXT("warning: You used a texture::no_fragmented whose dimensions are not a power of 2.")\
		                   SGE_TEXT(" This is slower to load and requires more texture memory because it needs atlasing and thus is not intuitive.")\
		                   SGE_TEXT(" The texture's size was ") << dim << SGE_TEXT(".\n")
		);

	return part_ptr(
		new part_fragmented(
			renderer::lock_rect(
				renderer::lock_rect::point_type(0,0),
				atlased_size(dim)),
			*this,
			need_atlasing(dim.w()),
			need_atlasing(dim.h())));
}

void sge::texture::no_fragmented::return_fragment(
	const part&)
{
	tex.reset();
}

const sge::renderer::texture_ptr
sge::texture::no_fragmented::get_texture() const
{
	return tex;
}

bool sge::texture::no_fragmented::repeatable() const
{
	return true;
}
