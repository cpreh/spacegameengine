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


#include "../source_blend_func.hpp"
#include "../parameters.hpp"
#include "../convert/source_blend_func.hpp"
#include "../../d3dinclude.hpp"
#include "../../devicefuncs/set_render_state.hpp"

void
sge::d3d9::state::source_blend_func(
	state::parameters const &_parameters,
	sge::renderer::state::source_blend_func::type const &_state
)
{
	d3d9::devicefuncs::set_render_state(
		_parameters.device(),
		D3DRS_SRCBLEND,
		state::convert::source_blend_func(
			_state
		)
	);
}
