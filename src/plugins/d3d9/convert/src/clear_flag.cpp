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


#include "../clear_flag.hpp"
#include "../../d3dinclude.hpp"
#include <fcppt/assert/unreachable.hpp>

DWORD
sge::d3d9::convert::clear_flag(
	sge::renderer::clear_flags::type const _type
)
{
	switch(
		_type
	)
	{
	case sge::renderer::clear_flags::depth_buffer:
		return D3DCLEAR_ZBUFFER;
	case sge::renderer::clear_flags::back_buffer:
		return D3DCLEAR_TARGET;
	case sge::renderer::clear_flags::stencil_buffer:
		return D3DCLEAR_STENCIL;
	}

	FCPPT_ASSERT_UNREACHABLE
}
