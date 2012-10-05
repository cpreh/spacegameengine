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
#include <sge/d3d9/devicefuncs/set_transform.hpp>
#include <sge/d3d9/state/convert/matrix_mode.hpp>
#include <sge/d3d9/state/ffp/transform/object.hpp>
#include <sge/d3d9/state/ffp/transform/state.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>	


sge::d3d9::state::ffp::transform::object::object(
	IDirect3DDevice9 &_device,
	sge::d3d9::state::ffp::transform::state const &_state
)
:
	device_(
		_device
	),
	state_(
		_state
	)
{
}

sge::d3d9::state::ffp::transform::object::~object()
{
}

void
sge::d3d9::state::ffp::transform::object::set(
	sge::renderer::state::ffp::transform::mode::type const _mode
) const
{
	sge::d3d9::devicefuncs::set_transform(
		device_,
		sge::d3d9::state::convert::matrix_mode(
			_mode
		),
		state_.matrix()
	);
}
