/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/state/ffp/lighting/light/directional.hpp>
#include <sge/opengl/state/ffp/lighting/light/point.hpp>
#include <sge/opengl/state/ffp/lighting/light/spot.hpp>
#include <sge/opengl/state/ffp/lighting/light/visitor.hpp>
#include <sge/renderer/state/ffp/lighting/light/directional_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/light/point_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/light/spot_fwd.hpp>


sge::opengl::state::ffp::lighting::light::visitor::result_type
sge::opengl::state::ffp::lighting::light::visitor::operator()(
	sge::renderer::state::ffp::lighting::light::directional const &_directional
) const
{
	return
		sge::opengl::state::ffp::lighting::light::directional(
			_directional
		);
}

sge::opengl::state::ffp::lighting::light::visitor::result_type
sge::opengl::state::ffp::lighting::light::visitor::operator()(
	sge::renderer::state::ffp::lighting::light::point const &_point
) const
{
	return
		sge::opengl::state::ffp::lighting::light::point(
			_point
		);
}

sge::opengl::state::ffp::lighting::light::visitor::result_type
sge::opengl::state::ffp::lighting::light::visitor::operator()(
	sge::renderer::state::ffp::lighting::light::spot const &_spot
) const
{
	return
		sge::opengl::state::ffp::lighting::light::spot(
			_spot
		);
}
