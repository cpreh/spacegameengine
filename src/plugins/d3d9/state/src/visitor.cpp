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
#include "../convert/cull_mode.hpp"
#include "../convert/depth_func.hpp"
#include "../convert/stencil_func.hpp"
#include "../convert/alpha_func.hpp"
#include "../convert/fog_mode.hpp"
#include "../convert/draw_mode.hpp"
#include "../convert/source_blend_func.hpp"
#include "../convert/dest_blend_func.hpp"
#include "../convert/stencil_op.hpp"
#include "../convert/stencil_op_value.hpp"
#include "../deferred/bundle.hpp"
#include "../deferred/object.hpp"
#include "../set_render_state_bool.hpp"
#include "../set_render_state_float.hpp"
#include "../../convert/to_color.hpp"
#include "../../devicefuncs/set_render_state.hpp"
#include <sge/renderer/state/var.hpp>
#include <sge/image/color/any/object.hpp>
#include <fcppt/variant/object_impl.hpp>

sge::d3d9::state::visitor::visitor(
	IDirect3DDevice9 *const _device,
	deferred::object &_deferred,
	state::clear &_clear_state
)
:
	device_(_device),
	deferred_(_deferred),
	clear_state_(_clear_state)
{
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::int_::type const _state
) const
{
	if(
		_state.state()
		== sge::renderer::state::int_::available_states::stencil_buffer_clear_val
	)
	{
		clear_state_.stencil(
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
		== sge::renderer::state::float_::available_states::depth_buffer_clear_val
	)
	{
		clear_state_.depth(
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
	case sge::renderer::state::bool_::available_states::clear_depth_buffer:
	case sge::renderer::state::bool_::available_states::clear_back_buffer:
	case sge::renderer::state::bool_::available_states::clear_stencil_buffer:
		return;
	case sge::renderer::state::bool_::available_states::write_alpha:
	case sge::renderer::state::bool_::available_states::write_blue:
	case sge::renderer::state::bool_::available_states::write_green:
	case sge::renderer::state::bool_::available_states::write_red:
		deferred_.add(
			deferred::bundle::color_write
		);
		return;
	case sge::renderer::state::bool_::available_states::enable_multi_sampling:
		return; // FIXME
	case sge::renderer::state::bool_::available_states::enable_alpha_blending:
		d3d9::state::set_render_state_bool(
			device_,
			D3DRS_SEPARATEALPHABLENDENABLE,
			_state.value()
		);
		break;
	default:
		break;
	}

	d3d9::state::set_render_state_bool(
		device_,
		state::convert::bool_(
			_state.state()
		),
		_state.value()
	);
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::color::type const _state
) const
{
	if(
		_state.state()
		== sge::renderer::state::color::available_states::back_buffer_clear_color
	)
	{
		clear_state_.color(
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
	d3d9::devicefuncs::set_render_state(
		device_,
		D3DRS_CULLMODE,
		state::convert::cull_mode(
			_state
		)
	);
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::depth_func::type const _state
) const
{
	bool const active(
		_state != sge::renderer::state::depth_func::off
	);

	d3d9::state::set_render_state_bool(
		device_,
		D3DRS_ZENABLE,
		active
	);

	if(
		active
	)
		d3d9::devicefuncs::set_render_state(
			device_,
			D3DRS_ZFUNC,
			state::convert::depth_func(
				_state
			)
		);
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::stencil_func::type const _state

) const
{
	bool const active(
		_state != sge::renderer::state::stencil_func::off
	);

	d3d9::state::set_render_state_bool(
		device_,
		D3DRS_STENCILENABLE,
		active
	);

	if(
		active
	)
		d3d9::devicefuncs::set_render_state(
			device_,
			D3DRS_STENCILFUNC,
			state::convert::stencil_func(
				_state
			)
		);
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::alpha_func::type const _state
) const
{
	bool const active(
		_state != sge::renderer::state::alpha_func::off
	);

	d3d9::state::set_render_state_bool(
		device_,
		D3DRS_ALPHATESTENABLE,
		active
	);

	if(
		active
	)
		d3d9::devicefuncs::set_render_state(
			device_,
			D3DRS_ALPHAFUNC,
			state::convert::alpha_func(
				_state
			)
		);
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::fog_mode::type const _state
) const
{
	bool const active(
		_state != sge::renderer::state::fog_mode::off
	);

	d3d9::state::set_render_state_bool(
		device_,
		D3DRS_FOGENABLE,
		active
	);

	// fog has an "off" mode
	d3d9::devicefuncs::set_render_state(
		device_,
		D3DRS_FOGTABLEMODE,
		state::convert::fog_mode(
			_state
		)
	);
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::draw_mode::type const _state
) const
{
	d3d9::devicefuncs::set_render_state(
		device_,
		D3DRS_FILLMODE,
		state::convert::draw_mode(
			_state
		)
	);
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::source_blend_func::type const _state
) const
{
	d3d9::devicefuncs::set_render_state(
		device_,
		D3DRS_SRCBLENDALPHA,
		state::convert::source_blend_func(
			_state
		)
	);
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::dest_blend_func::type const _state
) const
{
	d3d9::devicefuncs::set_render_state(
		device_,
		D3DRS_DESTBLENDALPHA,
		state::convert::dest_blend_func(
			_state
		)
	);
}

sge::d3d9::state::visitor::result_type
sge::d3d9::state::visitor::operator()(
	sge::renderer::state::stencil_op::type const _state
) const
{
	d3d9::devicefuncs::set_render_state(
		device_,
		state::convert::stencil_op(
			_state.state()
		),
		state::convert::stencil_op_value(
			_state.value()
		)
	);
}
