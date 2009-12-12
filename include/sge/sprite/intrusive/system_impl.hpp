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


#ifndef SGE_SPRITE_INTRUSIVE_SYSTEM_IMPL_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_SYSTEM_IMPL_HPP_INCLUDED

#include <sge/sprite/intrusive/system_decl.hpp>
#include <sge/sprite/detail/fill_geometry.hpp>
#include <sge/sprite/detail/render.hpp>
#include <sge/sprite/render_states.hpp>
#include <sge/sprite/system_base_impl.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/index_buffer.hpp>
#include <boost/foreach.hpp>

template<
	typename Choices
>
sge::sprite::intrusive::system<Choices>::system(
	renderer::device_ptr const rend
)
:
	base(
		rend
	)
{}

template<
	typename Choices
>
sge::sprite::intrusive::system<Choices>::~system()
{}

template<
	typename Choices
>
template<
	typename EqualFunction
>
void
sge::sprite::intrusive::system<Choices>::render_all(
	EqualFunction const &equal
)
{
	base::matrices();

	renderer::device_ptr const rend(
		base::renderer()
	);

	renderer::state::scoped const state_(
		rend,
		sprite::render_states()
	);

	BOOST_FOREACH(
		typename sprite_level_map::value_type const &v,
		sprite_levels
	)
		render(
			*v.second,
			equal
		);
}

template<
	typename Choices
>
template<
	typename EqualFunction
>
void
sge::sprite::intrusive::system<Choices>::render(
	order const order_,
	EqualFunction const &equal
)
{
	render(
		sprite_levels[
			order_
		],
		equal
	);
}

template<
	typename Choices
>
template<
	typename EqualFunction
>
void
sge::sprite::intrusive::system<Choices>::render(
	sprite_list const &sprites,
	EqualFunction const &equal
)
{
	if(sprites.empty())
		return;
	
	allocate_buffers(
		sprites.size()
	);

	renderer::vertex_buffer_ptr const vb(
		base::vertex_buffer()
	);

	renderer::index_buffer_ptr const ib(
		base::index_buffer()
	);

	sprite::detail::fill_geometry(
		sprites.begin(),
		sprites.end(),
		base::vertex_buffer(),
		base::index_buffer()
	);

	renderer::device_ptr const rend(
		base::renderer()
	);

	sprite::detail::render(
		sprites.begin(),
		sprites.end(),
		equal,
		rend,
		vb,
		ib
	);
}

template<
	typename Choices
>
void
sge::sprite::intrusive::system<Choices>::add(
	object &obj,
	order const order_
)
{
	sprite_levels[
		order_
	].push_back(
		obj
	);
}

#endif
