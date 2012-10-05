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


#include <sge/d3d9/convert/matrix.hpp>
#include <sge/d3d9/state/ffp/transform/make_states.hpp>
#include <sge/d3d9/state/ffp/transform/state.hpp>
#include <sge/renderer/state/ffp/transform/parameters.hpp>
#include <fcppt/math/matrix/transpose.hpp>


sge::d3d9::state::ffp::transform::state const
sge::d3d9::state::ffp::transform::make_states(
	sge::renderer::state::ffp::transform::parameters const &_parameters
)
{
	return
		sge::d3d9::state::ffp::transform::state(
			sge::d3d9::convert::matrix(
				fcppt::math::matrix::transpose(
					_parameters.matrix()
				)
			)
		);
}
