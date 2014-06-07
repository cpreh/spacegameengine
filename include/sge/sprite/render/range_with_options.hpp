/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SPRITE_RENDER_RANGE_WITH_OPTIONS_HPP_INCLUDED
#define SGE_SPRITE_RENDER_RANGE_WITH_OPTIONS_HPP_INCLUDED

#include <sge/sprite/detail/render/range.hpp>
#include <sge/sprite/detail/render/scoped_vertex.hpp>
#include <sge/sprite/render/parameters.hpp>
#include <sge/sprite/render/range_impl.hpp>
#include <sge/sprite/state/object_fwd.hpp>
#include <sge/sprite/state/options_fwd.hpp>
#include <sge/sprite/state/scoped_impl.hpp>


namespace sge
{
namespace sprite
{
namespace render
{

template<
	typename Choices,
	typename StateChoices
>
void
range_with_options(
	sge::sprite::render::parameters<
		StateChoices
	> const &_parameters,
	sge::sprite::render::range<
		Choices
	> const &_range,
	sge::sprite::state::object<
		StateChoices
	> &_states,
	sge::sprite::state::options<
		StateChoices
	> const &_options
)
{
	if(
		_range.empty()
	)
		return;

	sge::sprite::state::scoped<
		StateChoices
	> const states(
		_states.renderer(),
		_parameters.render_context(),
		_options,
		_states
	);

	sge::sprite::detail::render::scoped_vertex const scoped_vertex(
		_parameters,
		_range.vertex_buffer(),
		_options.vertex_options()
	);

	sge::sprite::detail::render::range(
		_parameters.render_context(),
		_range
	);
}

}
}
}

#endif
