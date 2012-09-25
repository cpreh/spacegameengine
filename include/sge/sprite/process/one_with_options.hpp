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


#ifndef SGE_SPRITE_PROCESS_ONE_WITH_OPTIONS_HPP_INCLUDED
#define SGE_SPRITE_PROCESS_ONE_WITH_OPTIONS_HPP_INCLUDED

#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/compare/nothing.hpp>
#include <sge/sprite/geometry/make_single_range.hpp>
#include <sge/sprite/process/geometry_options.hpp>
#include <sge/sprite/process/is_options.hpp>
#include <sge/sprite/process/with_options.hpp>
#include <sge/sprite/state/object_fwd.hpp>
#include <sge/sprite/state/options_fwd.hpp>
#include <fcppt/static_assert_expression.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace process
{

template<
	typename Options,
	typename RenderContext,
	typename Choices,
	typename Buffers,
	typename StateChoices
>
typename boost::enable_if<
	sge::sprite::process::is_options<
		Options
	>,
	void
>::type
one_with_options(
	RenderContext &_render_context,
	sge::sprite::object<
		Choices
	> const &_sprite,
	Buffers &_buffers,
	sge::sprite::state::object<
		StateChoices
	> &_states,
	sge::sprite::state::options<
		StateChoices
	> const &_state_options
)
{
	FCPPT_STATIC_ASSERT_EXPRESSION(
		Options::geometry_options
		!=
		sge::sprite::process::geometry_options::sort_and_update
	);

	sge::sprite::process::with_options<
		Options
	>(
		_render_context,
		sge::sprite::geometry::make_single_range(
			_sprite
		),
		_buffers,
		sge::sprite::compare::nothing(),
		_states,
		_state_options
	);
}

}
}
}

#endif
