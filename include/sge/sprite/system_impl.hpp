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


#ifndef SGE_SPRITE_SYSTEM_IMPL_HPP_INCLUDED
#define SGE_SPRITE_SYSTEM_IMPL_HPP_INCLUDED

#include <sge/sprite/system.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/detail/compare.hpp>
#include <sge/sprite/detail/render_states.hpp>
#include <sge/sprite/detail/fill_geometry.hpp>
#include <sge/sprite/detail/render.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/index_buffer.hpp>
#include <tr1/functional>
#include <iterator>

template<
	typename Choices,
	typename Elements
>
sge::sprite::system<Choices, Elements>::system(
	renderer::device_ptr const rend
)
:
 	system_base(
		rend
	)
{}

template<
	typename Choices,
	typename Elements
>
template<
	typename Iterator
>
void
sge::sprite::system<Choices, Elements>::render(
	Iterator const begin,
	Iterator const end,
	sort_method const &sort_fun,
	equal_method const &equal_fun
)
{
	if(begin == end)
		return;
	
	sort_fun(
		beg,
		end
	);

	allocate_buffers(
		std::distance(
			beg,
			end
		)
	);

	renderer::vertex_buffer_ptr const vb(
		vertex_buffer()
	);

	renderer::index_buffer_ptr const ib(
		index_buffer()
	);

	detail::fill_geometry(
		beg,
		end,
		vb,
		ib
	);

	matrices();

	renderer::device_ptr const rend(
		renderer()
	);

	renderer::state::scoped const state_(
		rend,
		detail::render_states()
	);

	detail::render(
		beg,
		end,
		equal_fun,
		rend,
		vb,
		ib
	);
}

template<
	typename Choices,
	typename Elements
>
void
sge::sprite::system<Choices, Elements>::render(
	object const &object_
)
{
	render(
		&object_,
		&object_ + 1
	);
}

sge::sprite::system::sort_method const
sge::sprite::system::default_sort(
	std::tr1::bind(
		std::stable_sort<
			sge::sprite::object *,
			bool (*)(sge::sprite::object const &, sge::sprite::object const &)
		>,
		std::tr1::placeholders::_1,
		std::tr1::placeholders::_2,
		sge::sprite::detail::less
	)
);

sge::sprite::system::equal_method const
sge::sprite::system::default_equal(
	sge::sprite::detail::equal);

#endif
