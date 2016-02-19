/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SPRITE_STATE_UNSET_HPP_INCLUDED
#define SGE_SPRITE_STATE_UNSET_HPP_INCLUDED

#include <sge/sprite/state/options_impl.hpp>
#include <sge/sprite/state/detail/unset_one.hpp>
#include <fcppt/mpl/for_each.hpp>


namespace sge
{
namespace sprite
{
namespace state
{

template<
	typename RenderContext,
	typename StateChoices
>
void
unset(
	RenderContext &_render_context,
	sge::sprite::state::options<
		StateChoices
	> const &_options
)
{
	fcppt::mpl::for_each<
		typename StateChoices::optional_elements
	>(
		sge::sprite::state::detail::unset_one<
			StateChoices
		>(
			_render_context,
			_options.elements()
		)
	);
}

}
}
}

#endif
