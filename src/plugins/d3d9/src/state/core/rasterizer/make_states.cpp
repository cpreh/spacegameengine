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
#include <sge/d3d9/convert/bool.hpp>
#include <sge/d3d9/state/render.hpp>
#include <sge/d3d9/state/render_vector.hpp>
#include <sge/d3d9/state/convert/cull_mode.hpp>
#include <sge/d3d9/state/convert/fill_mode.hpp>
#include <sge/d3d9/state/core/rasterizer/make_states.hpp>
#include <sge/renderer/state/core/rasterizer/parameters.hpp>
#include <fcppt/assign/make_container.hpp>


sge::d3d9::state::render_vector const
sge::d3d9::state::core::rasterizer::make_states(
	sge::renderer::state::core::rasterizer::parameters const &_parameters
)
{
	return
		fcppt::assign::make_container<
			sge::d3d9::state::render_vector
		>(
			sge::d3d9::state::render(
				D3DRS_CULLMODE,
				sge::d3d9::state::convert::cull_mode(
					_parameters.cull_mode()
				)
			)
		)(
			sge::d3d9::state::render(
				D3DRS_FILLMODE,
				sge::d3d9::state::convert::fill_mode(
					_parameters.fill_mode()
				)
			)
		)(
			sge::d3d9::state::render(
				D3DRS_SCISSORTESTENABLE,
				sge::d3d9::convert::bool_(
					_parameters.enable_scissor_test().get()
				)
			)
		);
}
