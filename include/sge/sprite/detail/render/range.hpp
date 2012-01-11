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


#ifndef SGE_SPRITE_DETAIL_RENDER_RANGE_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_RENDER_RANGE_HPP_INCLUDED

#include <sge/renderer/size_type.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/detail/visible.hpp>
#include <sge/sprite/detail/render/inner.hpp>
#include <sge/sprite/detail/render/set_textures.hpp>
#include <sge/sprite/detail/render/unset_textures.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace render
{

template<
	typename In,
	typename Comp,
	typename Buffers
>
void
range(
	In const _beg,
	In const _end,
	Comp const _comp,
	Buffers const &_buffers
)
{
	if(
		_beg == _end
	)
		return;

	typedef typename std::iterator_traits<
		In
	>::value_type object_type;

	sge::renderer::size_type offset(
		0
	);

	sge::sprite::detail::render::unset_textures<
		typename object_type::choices
	>(
		_buffers.renderer()
	);

	for(
		In
			cur(
				_beg
			),
			next(
				cur
			);
		cur != _end;
		cur = next
	)
	{
		sge::sprite::count num_objects(
			0u
		);

		while(
			next != _end
			&&
			!_comp(
				*cur,
				*next
			)
			&&
			!_comp(
				*next,
				*cur
			)
		)
		{
			++next;

			if(
				sge::sprite::detail::visible(
					*cur
				)
			)
				++num_objects;
		}

		sge::sprite::detail::render::set_textures(
			*cur,
			_buffers.renderer()
		);

		if(
			num_objects.get() == 0
		)
			continue;

		sge::sprite::detail::render::inner<
			typename object_type::choices
		>(
			_buffers.renderer(),
			offset,
			num_objects,
			_buffers
		);

		offset += num_objects.get();
	}

	sge::sprite::detail::render::unset_textures<
		typename object_type::choices
	>(
		_buffers.renderer()
	);
}

}
}
}
}

#endif
