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


#include <sge/renderer/state/ffp/lighting/ambient_color.hpp>
#include <sge/renderer/state/ffp/lighting/diffuse_from_vertex.hpp>
#include <sge/renderer/state/ffp/lighting/enabled.hpp>


sge::renderer::state::ffp::lighting::enabled::enabled(
	sge::renderer::state::ffp::lighting::ambient_color const &_ambient_color,
	sge::renderer::state::ffp::lighting::diffuse_from_vertex const _diffuse_from_vertex
)
:
	ambient_color_(
		_ambient_color
	),
	diffuse_from_vertex_(
		_diffuse_from_vertex
	)
{
}

sge::renderer::state::ffp::lighting::ambient_color const &
sge::renderer::state::ffp::lighting::enabled::ambient_color() const
{
	return ambient_color_;
}

sge::renderer::state::ffp::lighting::diffuse_from_vertex const
sge::renderer::state::ffp::lighting::enabled::diffuse_from_vertex() const
{
	return diffuse_from_vertex_;
}
