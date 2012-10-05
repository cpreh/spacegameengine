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
#include <sge/d3d9/devicefuncs/set_light.hpp>
#include <sge/d3d9/state/ffp/lighting/light/object.hpp>
#include <sge/d3d9/state/ffp/lighting/light/state.hpp>
#include <sge/renderer/state/index_count.hpp>
#include <sge/renderer/state/ffp/lighting/light/object.hpp>


sge::d3d9::state::ffp::lighting::light::object::object(
	IDirect3DDevice9 &_device,
	sge::d3d9::state::ffp::lighting::light::state const &_state
)
:
	sge::renderer::state::ffp::lighting::light::object(),
	device_(
		_device
	),
	state_(
		_state
	)
{
}

sge::d3d9::state::ffp::lighting::light::object::~object()
{
}

void
sge::d3d9::state::ffp::lighting::light::object::set(
	sge::renderer::state::index_count const _index
) const
{
	sge::d3d9::devicefuncs::set_light(
		device_,
		_index,
		state_.light()
	);
}
