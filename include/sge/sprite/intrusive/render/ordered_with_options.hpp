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


#ifndef SGE_SPRITE_INTRUSIVE_RENDER_ORDERED_WITH_OPTIONS_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_RENDER_ORDERED_WITH_OPTIONS_HPP_INCLUDED

#include <sge/sprite/detail/render/matrices.hpp>
#include <sge/sprite/detail/render/scoped_states.hpp>
#include <sge/sprite/detail/render/scoped_vertex.hpp>
#include <sge/sprite/intrusive/ordered_system_impl.hpp>
#include <sge/sprite/intrusive/detail/render_one.hpp>
#include <sge/sprite/render/geometry_options.hpp>
#include <sge/sprite/render/is_options.hpp>
#include <sge/sprite/render/vertex_options.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/static_assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace intrusive
{
namespace render
{

template<
	typename Options,
	typename Choices,
	typename Order,
	typename Buffers,
	typename Compare
>
typename boost::enable_if<
	sge::sprite::render::is_options<
		Options
	>,
	void
>::type
ordered_with_options(
	sge::sprite::intrusive::ordered_system<
		Choices,
		Order
	> &_system,
	Buffers &_buffers,
	Compare const &_compare
)
{
	BOOST_STATIC_ASSERT(
		Options::vertex_options
		== sge::sprite::render::vertex_options::declaration
		||
		Options::vertex_options
		== sge::sprite::render::vertex_options::nothing
	);

	BOOST_STATIC_ASSERT(
		Options::geometry_options
		!= sge::sprite::render::geometry_options::nothing
	);

	typedef typename sge::sprite::intrusive::ordered_system<
		Choices,
		Order
	>::system system;

	sge::sprite::detail::render::matrices<
		Options::matrix_options
	>(
		_buffers.renderer()
	);

	sge::sprite::detail::render::scoped_states<
		Choices,
		Options::state_options
	> const states(
		_buffers.renderer()
	);

	sge::sprite::detail::render::scoped_vertex<
		Options::vertex_options
	> const vertex(
		_buffers.renderer(),
		_buffers.vertex_declaration(),
		_buffers.vertex_buffer()
	);

	_system.for_each(
		std::tr1::bind(
			sge::sprite::intrusive::detail::render_one<
				Options,
				Buffers,
				Compare,
				typename system::range_type
			>,
			fcppt::ref(
				_buffers
			),
			fcppt::cref(
				_compare
			),
			std::tr1::placeholders::_1
		)
	);
}

}
}
}
}

#endif
