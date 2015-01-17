/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/d3d9/state/render_vector.hpp>
#include <sge/d3d9/state/convert/bool_to_dword.hpp>
#include <sge/d3d9/state/convert/depth_func.hpp>
#include <sge/d3d9/state/core/depth_stencil/depth/visitor.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/enabled.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/off_fwd.hpp>


sge::d3d9::state::core::depth_stencil::depth::visitor::result_type
sge::d3d9::state::core::depth_stencil::depth::visitor::operator()(
	sge::renderer::state::core::depth_stencil::depth::off const &
) const
{
	return
		sge::d3d9::state::render_vector{
			sge::d3d9::state::render(
				D3DRS_ZENABLE,
				D3DZB_FALSE
			)
		};
}

sge::d3d9::state::core::depth_stencil::depth::visitor::result_type
sge::d3d9::state::core::depth_stencil::depth::visitor::operator()(
	sge::renderer::state::core::depth_stencil::depth::enabled const &_enabled
) const
{
	return
		sge::d3d9::state::render_vector{
			sge::d3d9::state::render(
				D3DRS_ZENABLE,
				D3DZB_TRUE
			),
			sge::d3d9::state::render(
				D3DRS_ZFUNC,
				sge::d3d9::state::convert::depth_func(
					_enabled.func()
				)
			),
			sge::d3d9::state::render(
				D3DRS_ZWRITEENABLE,
				sge::d3d9::state::convert::bool_to_dword(
					_enabled.write_enable().get()
				)
			)
		};
}
