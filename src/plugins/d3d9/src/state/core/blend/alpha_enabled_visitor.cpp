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


#include <sge/d3d9/state/render.hpp>
#include <sge/d3d9/state/render_vector.hpp>
#include <sge/d3d9/state/core/blend/alpha_enabled_visitor.hpp>
#include <sge/d3d9/state/convert/dest_blend_func.hpp>
#include <sge/d3d9/state/convert/source_blend_func.hpp>
#include <sge/renderer/state/core/blend/combined.hpp>
#include <sge/renderer/state/core/blend/separate.hpp>
#include <fcppt/assign/make_container.hpp>


sge::d3d9::state::core::blend::alpha_enabled_visitor::result_type
sge::d3d9::state::core::blend::alpha_enabled_visitor::operator()(
	sge::renderer::state::core::blend::combined const &_combined
) const
{
	return
		fcppt::assign::make_container<
			sge::d3d9::state::render_vector
		>(
			sge::d3d9::state::render(
				D3DRS_SEPARATEALPHABLENDENABLE,
				FALSE
			)
		)(
			sge::d3d9::state::render(
				D3DRS_SRCBLEND,
				sge::d3d9::state::convert::source_blend_func(
					_combined.source()
				)
			)
		)(
			sge::d3d9::state::render(
				D3DRS_DESTBLEND,
				sge::d3d9::state::convert::dest_blend_func(
					_combined.dest()
				)
			)
		);	
}

sge::d3d9::state::core::blend::alpha_enabled_visitor::result_type
sge::d3d9::state::core::blend::alpha_enabled_visitor::operator()(
	sge::renderer::state::core::blend::separate const &_separate
) const
{
	return
		fcppt::assign::make_container<
			sge::d3d9::state::render_vector
		>(
			sge::d3d9::state::render(
				D3DRS_SEPARATEALPHABLENDENABLE,
				TRUE
			)
		)(
			sge::d3d9::state::render(
				D3DRS_SRCBLEND,
				sge::d3d9::state::convert::source_blend_func(
					_separate.color_source().get()
				)
			)
		)(
			sge::d3d9::state::render(
				D3DRS_DESTBLEND,
				sge::d3d9::state::convert::dest_blend_func(
					_separate.color_dest().get()
				)
			)
		)(
			sge::d3d9::state::render(
				D3DRS_SRCBLENDALPHA,
				sge::d3d9::state::convert::source_blend_func(
					_separate.alpha_source().get()
				)
			)
		)(
			sge::d3d9::state::render(
				D3DRS_DESTBLENDALPHA,
				sge::d3d9::state::convert::dest_blend_func(
					_separate.alpha_dest().get()
				)
			)
		);
}
