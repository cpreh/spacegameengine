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


#include "../matrix_mode.hpp"
#include "../../d3dinclude.hpp"
#include <sge/renderer/matrix_mode.hpp>
#include <fcppt/assert/unreachable.hpp>

D3DTRANSFORMSTATETYPE
sge::d3d9::convert::matrix_mode(
	sge::renderer::matrix_mode::type const _mode
)
{
	switch(
		_mode
	)
	{
	case sge::renderer::matrix_mode::world:
		return D3DTS_VIEW;
	case sge::renderer::matrix_mode::projection:
		return D3DTS_PROJECTION;
	case sge::renderer::matrix_mode::texture:
		return D3DTS_TEXTURE0;
	case sge::renderer::matrix_mode::size:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
