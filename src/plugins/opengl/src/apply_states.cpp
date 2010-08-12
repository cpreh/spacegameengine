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


#include "../apply_states.hpp"
#include "../split_states.hpp"
#include "../state_visitor.hpp"
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/parameters.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <boost/foreach.hpp>

void
sge::opengl::apply_states(
	opengl::context::object &_context,
	sge::renderer::state::list &_current_states,
	sge::renderer::state::list const &_new_states,
	sge::renderer::parameters const &_param
)
{
	opengl::split_states split(
		_current_states
	);

	opengl::state_visitor const visitor(
		_context,
		split,
		_param.depth_buffer(),
		_param.stencil_buffer()
	);

	BOOST_FOREACH(
		renderer::state::any const &state,
		_new_states.values()
	)
	{
		_current_states.overwrite(
			state
		);

		fcppt::variant::apply_unary(
			visitor,
			state
		);
	}
}
