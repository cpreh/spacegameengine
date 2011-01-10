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


#ifndef SGE_SPRITE_DETAIL_RENDER_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_RENDER_HPP_INCLUDED

#include <sge/sprite/detail/render_inner.hpp>
#include <sge/sprite/detail/set_texture_pre.hpp>
#include <sge/sprite/detail/set_texture.hpp>
#include <sge/renderer/size_type.hpp>
#include <iterator>

namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename In,
	typename Comp,
	typename Buffers
>
void
render(
	In const _beg,
	In const _end,
	Comp const _comp,
	renderer::device_ptr const _rend,
	Buffers const &_buffers
)
{
	typedef typename std::iterator_traits<
		In
	>::value_type object_type;

	renderer::size_type offset(0);

	detail::set_texture_pre<
		typename object_type::elements
	>(
		_rend
	);

	for(
		In cur(_beg), next(cur);
		cur != _end; cur = next
	)
	{
		renderer::size_type num_objects(0);

		while(
			next != _end && _comp(*cur, *next)
		)
		{
			++next;

			if(
				detail::visible(
					*cur
				)
			)
				++num_objects;
		}

		detail::set_texture(
			*cur,
			_rend
		);

		detail::render_inner<
			typename object_type::choices::elements
		>(
			_rend,
			offset,
			num_objects,
			_buffers
		);

		offset += num_objects;
	}
}

}
}
}

#endif
