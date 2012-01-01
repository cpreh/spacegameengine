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


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/set_render_state.hpp>
#include <sge/d3d9/state/convert/color_write.hpp>
#include <sge/d3d9/state/deferred/color_write.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/extract_trampoline.hpp>
#include <sge/renderer/state/list_fwd.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/state/bool/trampoline.hpp>


namespace
{

DWORD
make_flag(
	sge::renderer::state::list const &,
	sge::renderer::state::bool_::trampoline const &
);

}

void
sge::d3d9::state::deferred::color_write(
	IDirect3DDevice9 *const _device,
	sge::renderer::state::list const &_list
)
{
	devicefuncs::set_render_state(
		_device,
		D3DRS_COLORWRITEENABLE,
		::make_flag(
			_list,
			renderer::state::bool_::write_alpha
		)
		|
		::make_flag(
			_list,
			renderer::state::bool_::write_blue
		)
		|
		::make_flag(
			_list,
			renderer::state::bool_::write_green
		)
		|
		::make_flag(
			_list,
			renderer::state::bool_::write_red
		)
	);
}

namespace
{

DWORD
make_flag(
	sge::renderer::state::list const &_list,
	sge::renderer::state::bool_::trampoline const &_state
)
{
	return
		sge::renderer::state::extract_trampoline(
			_list,
			_state
		)
		?
			sge::d3d9::state::convert::color_write(
				_state.state()
			)
		:
			0
		;
}

}
