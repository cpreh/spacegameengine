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


#include <sge/d3d9/state/render_vector.hpp>
#include <sge/d3d9/state/core/blend/alpha_visitor.hpp>
#include <sge/d3d9/state/core/blend/make_states.hpp>
#include <sge/d3d9/state/core/blend/write_mask.hpp>
#include <sge/renderer/state/core/blend/parameters.hpp>
#include <fcppt/algorithm/join.hpp>
#include <fcppt/variant/apply_unary.hpp>


sge::d3d9::state::render_vector
sge::d3d9::state::core::blend::make_states(
	sge::renderer::state::core::blend::parameters const &_parameters
)
{
	return
		fcppt::algorithm::join(
			sge::d3d9::state::render_vector{
				sge::d3d9::state::core::blend::write_mask(
					_parameters.write_mask()
				)
			},
			fcppt::variant::apply_unary(
				sge::d3d9::state::core::blend::alpha_visitor(),
				_parameters.alpha_variant()
			)
		);
}
