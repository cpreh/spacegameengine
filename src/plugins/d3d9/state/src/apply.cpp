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


#include "../apply.hpp"
#include "../parameters.hpp"
#include "../visitor.hpp"
#include "../deferred/object.hpp"
#include <sge/renderer/state/any.hpp>
#include <sge/renderer/state/apply.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/cref.hpp>

void
sge::d3d9::state::apply(
	IDirect3DDevice9 *const _device,
	state::clear &_clear_state,
	sge::renderer::state::list &_current_states,
	sge::renderer::state::list const &_new_states
)
{
	d3d9::state::deferred::object deferred_states(
		_device
	);

	d3d9::state::visitor const visitor(
		state::parameters(
			_device,
			deferred_states,
			_clear_state
		)
	);

	sge::renderer::state::apply(
		_current_states,
		_new_states,
		std::tr1::bind(
			&fcppt::variant::apply_unary<
				d3d9::state::visitor,
				sge::renderer::state::any
			>,
			fcppt::cref(
				visitor
			),
			std::tr1::placeholders::_1
		)
	);

	deferred_states.update(
		_current_states
	);
}
