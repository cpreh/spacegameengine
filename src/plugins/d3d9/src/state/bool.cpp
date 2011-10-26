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


#include <sge/d3d9/state/bool.hpp>
#include <sge/d3d9/state/parameters.hpp>
#include <sge/d3d9/state/set_render_state_bool.hpp>
#include <sge/d3d9/state/convert/bool.hpp>
#include <sge/d3d9/state/deferred/bundle.hpp>
#include <sge/d3d9/state/deferred/object.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/var.hpp>

void
sge::d3d9::state::bool_(
	state::parameters const &_parameters,
	sge::renderer::state::bool_::type const &_state
)
{
	switch(
		_state.state()
	)
	{
	case sge::renderer::state::bool_::available_states::clear_depth_buffer:
	case sge::renderer::state::bool_::available_states::clear_back_buffer:
	case sge::renderer::state::bool_::available_states::clear_stencil_buffer:
		return;
	case sge::renderer::state::bool_::available_states::write_alpha:
	case sge::renderer::state::bool_::available_states::write_blue:
	case sge::renderer::state::bool_::available_states::write_green:
	case sge::renderer::state::bool_::available_states::write_red:
		_parameters.deferred().add(
			deferred::bundle::color_write
		);
		return;
	case sge::renderer::state::bool_::available_states::enable_multi_sampling:
		return; // FIXME
	default:
		break;
	}

	d3d9::state::set_render_state_bool(
		_parameters.device(),
		state::convert::bool_(
			_state.state()
		),
		_state.value()
	);
}
