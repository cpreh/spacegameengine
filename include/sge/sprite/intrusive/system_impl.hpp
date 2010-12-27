/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/sprite/intrusive/adder_impl.hpp>
#include <sge/sprite/detail/fill_geometry.hpp>
#include <sge/sprite/detail/optional_size.hpp>
#include <sge/sprite/detail/render.hpp>
#include <sge/sprite/set_matrices.hpp>
#include <sge/sprite/render_states.hpp>
#include <sge/sprite/system_base_impl.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/renderer/size_type.hpp>
#include <fcppt/optional_impl.hpp>
#include <boost/foreach.hpp>

template<
	typename Choices
>
sge::sprite::intrusive::system<Choices>::system(
	renderer::device_ptr const _rend
)
:
	base(
		_rend
	),
	sprite_levels_(),
	adder_(
		sprite_levels_
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
	EqualFunction const &_equal
)
{
	sprite::set_matrices(
		base::renderer()
	);

	sge::renderer::state::scoped const state(
		base::renderer(),
		sprite::render_states<
			Choices
		>()
	);

	render_all_advanced(
		_equal
	);
}

template<
	typename Choices
>
template<
	typename EqualFunction
>
void
sge::sprite::intrusive::system<Choices>::render_all_advanced(
	EqualFunction const &_equal
)
{
	BOOST_FOREACH(
		typename level_map::value_type const &level,
		sprite_levels_
	)
		render_list(
			*level.second,
			_equal
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
	order const _order,
	EqualFunction const &_equal
)
{
	sprite::set_matrices(
		base::renderer()
	);

	sge::renderer::state::scoped const state(
		base::renderer(),
		sprite::render_states<
			Choices
		>()
	);

	render_advanced(
		_order,
		_equal
	);
}

template<
	typename Choices
>
template<
	typename EqualFunction
>
void
sge::sprite::intrusive::system<Choices>::render_advanced(
	order const _order,
	EqualFunction const &_equal
)
{
	render_list(
		sprite_levels_[
			_order
		],
		_equal
	);
}

template<
	typename Choices
>
template<
	typename EqualFunction
>
void
sge::sprite::intrusive::system<Choices>::render_list(
	list const &_sprites,
	EqualFunction const &_equal
)
{
	if(
		_sprites.empty()
	)
		return;
	
	// TODO: better track the sprites size
	renderer::size_type const sprite_count(
		_sprites.size()
	);

	base::allocate_buffers(
		sprite_count
	);

	sprite::detail::fill_geometry(
		_sprites.begin(),
		_sprites.end(),
		base::buffers(),
		sprite::detail::optional_size(
			sprite_count
		)
	);

	renderer::scoped_vertex_buffer const vb_context(
		base::renderer(),
		base::vertex_buffer()
	);

	sprite::detail::render(
		_sprites.begin(),
		_sprites.end(),
		_equal,
		base::renderer(),
		base::buffers()
	);
}

template<
	typename Choices
>
typename sge::sprite::intrusive::system<Choices>::adder_base *
sge::sprite::intrusive::system<Choices>::adder()
{
	return &adder_;
}

#endif
