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


#ifndef SGE_SPRITE_DETAIL_FILL_GEOMETRY_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_FILL_GEOMETRY_HPP_INCLUDED

#include <sge/sprite/detail/vertex_format.hpp>
#include <sge/sprite/detail/index_generator.hpp>
#include <sge/sprite/detail/constants.hpp>
#include <sge/sprite/detail/helper.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/index_buffer.hpp>
#include <sge/renderer/scoped_index_lock.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/index/generate.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/texture/part.hpp>
#include <sge/texture/area_texc.hpp>
#include <sge/math/almost_zero.hpp>
#include <boost/variant/get.hpp>

namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename It
>
void fill_geometry(
	It begin,
	It const end,
	renderer::vertex_buffer_ptr const vb,
	renderer::index_buffer_ptr const ib
)
{
	renderer::scoped_vertex_lock const vblock(
		vb,
		renderer::lock_mode::writeonly
	);

	typedef renderer::vf::view<
		vertex_format
	> vertex_view;

	vertex_view const vertices(vblock.value());

	vertex_view::iterator vb_it = vertices.begin();

	renderer::size_type count(0);

	for(It it(begin); it != end; ++it)
	{
		object const &spr(*it);

		if(!visible(spr))
			continue;
//		if(!spr.visible())
//			continue;

		if(math::almost_zero(spr.rotation()))
			fill_position(vb_it, spr.rect(), spr.z());
		else
			fill_position_rotated(vb_it, spr.rect(), spr.rotation(), spr.rotation_center(), spr.z());

		if(texture::const_part_ptr const tex = spr.texture())
			fill_tex_coordinates(vb_it, texture::area_texc(tex, spr.repeat()));

		vb_it = fill_color(vb_it, spr.color());

		++count;
	}

	renderer::index::generate(
		renderer::scoped_index_lock(
			ib,
			renderer::lock_mode::writeonly,
			0,
			count * detail::indices_per_sprite
		).value(),
		index_generator());
}

}
}
}

#endif
