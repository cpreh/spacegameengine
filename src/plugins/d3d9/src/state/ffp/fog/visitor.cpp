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
#include <sge/d3d9/convert/to_color.hpp>
#include <sge/d3d9/state/render.hpp>
#include <sge/d3d9/state/render_vector.hpp>
#include <sge/d3d9/state/convert/float_to_dword.hpp>
#include <sge/d3d9/state/convert/fog_mode.hpp>
#include <sge/d3d9/state/ffp/fog/visitor.hpp>
#include <sge/renderer/state/ffp/fog/enabled.hpp>
#include <sge/renderer/state/ffp/fog/off_fwd.hpp>
#include <fcppt/assign/make_container.hpp>


sge::d3d9::state::ffp::fog::visitor::result_type
sge::d3d9::state::ffp::fog::visitor::operator()(
	sge::renderer::state::ffp::fog::off const &
) const
{
	return
		fcppt::assign::make_container<
			sge::d3d9::state::render_vector
		>(
			sge::d3d9::state::render(
				D3DRS_FOGENABLE,
				FALSE
			)
		);
}

sge::d3d9::state::ffp::fog::visitor::result_type
sge::d3d9::state::ffp::fog::visitor::operator()(
	sge::renderer::state::ffp::fog::enabled const &_enabled
) const
{
	return
		fcppt::assign::make_container<
			sge::d3d9::state::render_vector
		>(
			sge::d3d9::state::render(
				D3DRS_FOGENABLE,
				TRUE
			)
		)(
			sge::d3d9::state::render(
				D3DRS_FOGTABLEMODE,
				sge::d3d9::state::convert::fog_mode(
					_enabled.mode()
				)
			)
		)(
			sge::d3d9::state::render(
				D3DRS_FOGCOLOR,
				sge::d3d9::convert::to_color(
					_enabled.color().get()
				)
			)
		)(
			sge::d3d9::state::render(
				D3DRS_FOGSTART,
				sge::d3d9::state::convert::float_to_dword(
					_enabled.start().get()
				)
			)
		)(
			sge::d3d9::state::render(
				D3DRS_FOGEND,
				sge::d3d9::state::convert::float_to_dword(
					_enabled.end().get()
				)
			)
		)(
			sge::d3d9::state::render(
				D3DRS_FOGDENSITY,
				sge::d3d9::state::convert::float_to_dword(
					_enabled.density().get()
				)
			)
		);
}
