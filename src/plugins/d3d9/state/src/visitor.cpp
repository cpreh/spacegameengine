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


#include "../visitor.hpp"
#include "../clear.hpp"
#include "../convert/int.hpp"
#include "../convert/uint.hpp"
#include "../convert/float.hpp"
#include "../convert/bool.hpp"
#include "../convert/color.hpp"
#include "../convert/clear.hpp"
#include "../set_render_state_float.hpp"
#include "../../convert/to_color.hpp"
#include "../../devicefuncs/set_render_state.hpp"
#include <sge/renderer/state/var.hpp>
#include <fcppt/variant/object_impl.hpp>

sge::d3d9::state::visitor::visitor(
	IDirect3DDevice9 *const _device,
	state::clear &_clear
)
:
	device_(_device),
	clear_(_clear)
{
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::int_::type const _state
) const
{
	if(
		_state.state()
		== sge::renderer::state::int_::available_states::stencil_clear_val
	)
	{
		clear_.stencil(
			static_cast<
				DWORD
			>(
				_state.value()
			)
		);

		return;
	}

	d3d9::devicefuncs::set_render_state(
		device_,
		state::convert::int_(
			_state.state()
		),
		static_cast<
			DWORD
		>(
			_state.value()
		)
	);
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::uint::type const _state
) const
{
	d3d9::devicefuncs::set_render_state(
		device_,
		state::convert::uint(
			_state.state()
		),
		static_cast<
			DWORD
		>(
			_state.value()
		)
	);
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::float_::type const _state
) const
{
	if(
		_state.state()
		== sge::renderer::state::float_::available_states::zbuffer_clear_val
	)
	{
		clear_.depth(
			_state.value()
		);

		return;
	}

	d3d9::state::set_render_state_float(
		device_,
		state::convert::float_(
			_state.state()
		),
		_state.value()
	);
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::bool_::type const _state
) const
{
	switch(
		_state.state()
	)
	{
	case sge::renderer::state::bool_::available_states::clear_zbuffer:
	case sge::renderer::state::bool_::available_states::clear_backbuffer:
	case sge::renderer::state::bool_::available_states::clear_stencil:
		clear_.flag(
			state::convert::clear(
				_state.state()
			),
			_state.value()
		);

		return;
	case sge::renderer::state::bool_::available_states::enable_multi_sampling:
		return; // FIXME
	default:
		break;
	}

	d3d9::devicefuncs::set_render_state(
		device_,
		state::convert::bool_(
			_state.state()
		),
		_state.value()
		?
			TRUE
		:
			FALSE
	);
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::color::type const _state
) const
{
	if(
		_state.state()
		== sge::renderer::state::color::available_states::clear_color
	)
	{
		clear_.color(
			d3d9::convert::to_color(	
				_state.value()
			)
		);

		return;
	}

	d3d9::devicefuncs::set_render_state(
		device_,
		state::convert::color(
			_state.state()
		),
		static_cast<
			DWORD
		>(
			d3d9::convert::to_color(
				_state.value()
			)
		)
	);
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::cull_mode::type const _state
) const
{
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::depth_func::type const _state
) const
{
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::stencil_func::type const _state

) const
{
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::alpha_func::type const _state
) const
{
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::fog_mode::type const _state
) const
{
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::draw_mode::type const _state
) const
{
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::source_blend_func::type const _state
) const
{
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::dest_blend_func::type const _state
) const
{
}

