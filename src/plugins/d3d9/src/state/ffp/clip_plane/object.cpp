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
#include <sge/d3d9/devicefuncs/set_clip_plane.hpp>
#include <sge/d3d9/state/ffp/clip_plane/object.hpp>
#include <sge/d3d9/state/ffp/clip_plane/state.hpp>
#include <sge/renderer/state/index_count.hpp>
#include <sge/renderer/state/ffp/clip_plane/object.hpp>


sge::d3d9::state::ffp::clip_plane::object::object(
	IDirect3DDevice9 &_device,
	sge::d3d9::state::ffp::clip_plane::state const &_state
)
:
	sge::renderer::state::ffp::clip_plane::object(),
	device_(
		_device
	),
	state_(
		_state
	)
{
}

sge::d3d9::state::ffp::clip_plane::object::~object()
{
}

void
sge::d3d9::state::ffp::clip_plane::object::set(
	sge::renderer::state::index_count const _index
) const
{
	sge::d3d9::devicefuncs::set_clip_plane(
		device_,
		_index,
		state_.area()
	);
}
