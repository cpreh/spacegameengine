/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/d3d9/state/render.hpp>
#include <sge/d3d9/state/core/blend/write_mask.hpp>
#include <sge/renderer/state/core/blend/write_mask.hpp>


namespace
{

DWORD
make_flag(
	bool,
	DWORD
);

}

sge::d3d9::state::render const
sge::d3d9::state::core::blend::write_mask(
	sge::renderer::state::core::blend::write_mask const &_write_mask
)
{
	return
		sge::d3d9::state::render(
			D3DRS_COLORWRITEENABLE,
			make_flag(
				_write_mask.write_alpha().get(),
				D3DCOLORWRITEENABLE_ALPHA
			)
			|
			make_flag(
				_write_mask.write_red().get(),
				D3DCOLORWRITEENABLE_RED
			)
			|
			make_flag(
				_write_mask.write_green().get(),
				D3DCOLORWRITEENABLE_GREEN
			)
			|
			make_flag(
				_write_mask.write_blue().get(),
				D3DCOLORWRITEENABLE_BLUE
			)
		);
}

namespace
{

DWORD
make_flag(
	bool const _enabled,
	DWORD const _flag
)
{
	return
		_enabled
		?
			_flag
		:
			0u
		;
}

}
