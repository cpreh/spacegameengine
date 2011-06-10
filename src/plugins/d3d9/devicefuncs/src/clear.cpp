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


#include "../clear.hpp"
#include "../../convert/clear_flag.hpp"
#include "../../state/clear.hpp"
#include <sge/renderer/exception.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/text.hpp>

namespace
{

DWORD
make_flag(
	sge::renderer::clear_flags_field const &,
	sge::renderer::clear_flags::type
);

}

void
sge::d3d9::devicefuncs::clear(
	IDirect3DDevice9 *const _device,
	renderer::clear_flags_field const &_flags,
	state::clear const &_state
)
{
	if(
		_flags
		&&
		_device->Clear(
			0,
			0,
			::make_flag(
				_flags,
				sge::renderer::clear_flags::back_buffer
			)
			|
			::make_flag(
				_flags,
				sge::renderer::clear_flags::depth_buffer
			)
			|
			::make_flag(
				_flags,
				sge::renderer::clear_flags::stencil_buffer
			),
			_state.color(),
			_state.depth(),
			_state.stencil()
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("Clear() failed!")
		);
}

namespace
{

DWORD
make_flag(
	sge::renderer::clear_flags_field const &_field,
	sge::renderer::clear_flags::type const _flag
)
{
	return
		_field[
				_flag
		]
		?
			sge::d3d9::convert::clear_flag(
				_flag
			)
		:
			0;
}

}
