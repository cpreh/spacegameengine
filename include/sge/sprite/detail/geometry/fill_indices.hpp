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


#ifndef SGE_SPRITE_DETAIL_GEOMETRY_FILL_INDICES_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_GEOMETRY_FILL_INDICES_HPP_INCLUDED

#include <sge/renderer/first_index.hpp>
#include <sge/renderer/index_buffer_fwd.hpp>
#include <sge/renderer/index_count.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/scoped_index_lock.hpp>
#include <sge/renderer/index/any/generate.hpp>
#include <sge/renderer/index/any/make_view.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/detail/geometry/index_generator.hpp>
#include <sge/sprite/detail/geometry/indices_per_sprite.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace geometry
{

template<
	typename Choices
>
void
fill_indices(
	sge::renderer::index_buffer &_ib,
	sge::sprite::count const _count
)
{
	sge::renderer::scoped_index_lock const lock(
		_ib,
		sge::renderer::lock_mode::writeonly,
		sge::renderer::first_index(
			0
		),
		sge::renderer::index_count(
			_count.get()
			*
			sge::sprite::detail::geometry::indices_per_sprite<
				Choices
			>::value
		)
	);

	sge::renderer::index::any::generate(
		sge::renderer::index::any::make_view(
			lock.value()
		),
		sge::sprite::detail::geometry::index_generator<
			Choices
		>()
	);
}

}
}
}
}

#endif
