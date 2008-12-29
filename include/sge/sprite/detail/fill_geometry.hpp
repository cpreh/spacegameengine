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


#ifndef SGE_SPRITE_DETAIL_FILL_GEOMETRY_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_FILL_GEOMETRY_HPP_INCLUDED

#include "vertex_format.hpp"
#include "helper.hpp"
#include "../../renderer/vertex_buffer.hpp"
#include "../../renderer/index_buffer.hpp"
#include "../../renderer/scoped_index_lock.hpp"
#include "../../renderer/scoped_vertex_lock.hpp"
#include "../../renderer/vf/view.hpp"
#include "../../renderer/vf/iterator.hpp"
#include "../../renderer/vf/vertex.hpp"
#include "../../texture/part.hpp"
#include "../../texture/area_texc.hpp"
#include <boost/variant/get.hpp>

namespace sge
{
namespace sprite
{
namespace detail
{

template<typename It>
void fill_geometry(
	It begin,
	It const end,
	renderer::vertex_buffer_ptr const vb,
	renderer::index_buffer_ptr const ib)
{
	renderer::scoped_index_lock const iblock(
		renderer::make_scoped_lock(
			ib,
			renderer::lock_flags::writeonly));

	renderer::scoped_vertex_lock const vblock(
		renderer::make_scoped_lock(
			vb,
			renderer::lock_flags::writeonly));

	typedef renderer::vf::view<
		vertex_format
	> vertex_view;

	index_view const indices(boost::get<index_view>(iblock.value()));
	vertex_view const vertices(vblock.value());

	index_view::iterator ib_it = indices.begin();

	vertex_view::iterator vb_it = vertices.begin();

	for(It it(begin); it != end; ++it)
	{
		object const &spr(*it);

		if(!spr.visible())
			continue;
		ib_it = fill_indices(ib_it, static_cast<index_view::value_type>(vb_it - vertices.begin()));

		if(math::almost_zero(spr.rotation()))
			fill_position(vb_it, spr.rect(), spr.z());
		else
			fill_position_rotated(vb_it, spr.rect(), spr.rotation(), spr.rotation_center(), spr.z());

		if(texture::const_part_ptr const tex = spr.texture())
			fill_tex_coordinates(vb_it, texture::area_texc(tex, spr.repeat()));

		vb_it = fill_color(vb_it, spr.color());
	}
}

}
}
}

#endif
