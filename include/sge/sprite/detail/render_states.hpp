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


#ifndef SGE_SPRITE_DETAIL_RENDER_STATES_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_RENDER_STATES_HPP_INCLUDED

#include <sge/sprite/detail/normal_render_states.hpp>
#include <sge/sprite/with_unspecified_dim.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/state/bool.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/utility/enable_if.hpp>

namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Choices,
	typename Enable = void
>
struct render_states;

template<
	typename Choices
>
struct render_states<
	Choices,
	typename boost::enable_if<
		boost::mpl::contains<
			typename Choices::elements,
			sprite::with_unspecified_dim
		>
	>::type
>
{
	static sge::renderer::state::list const value;	
};

template<
	typename Choices
>
struct render_states<
	Choices,
	typename boost::disable_if<
		boost::mpl::contains<
			typename Choices::elements,
			sprite::with_unspecified_dim
		>
	>::type
>
{
	static sge::renderer::state::list const value;	
};

}
}
}

template<
	typename Choices
>
sge::renderer::state::list const
sge::sprite::detail::render_states<
	Choices,
	typename boost::enable_if<
		boost::mpl::contains<
			typename Choices::elements,
			sge::sprite::with_unspecified_dim
		>
	>::type
>::value =
sge::sprite::detail::normal_render_states()
(
	sge::renderer::state::bool_::enable_point_sprites = true
);

template<
	typename Choices
>
sge::renderer::state::list const
sge::sprite::detail::render_states<
	Choices,
	typename boost::disable_if<
		boost::mpl::contains<
			typename Choices::elements,
			sge::sprite::with_unspecified_dim
		>
	>::type
>::value =
sge::sprite::detail::normal_render_states();

#endif
