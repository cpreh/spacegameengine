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
#include <sge/d3d9/devicefuncs/set_sampler_state.hpp>
#include <sge/d3d9/state/core/sampler/object.hpp>
#include <sge/d3d9/state/core/sampler/state_vector.hpp>
#include <sge/renderer/state/core/sampler/object.hpp>
#include <sge/renderer/texture/stage.hpp>


sge::d3d9::state::core::sampler::object::object(
	IDirect3DDevice9 &_device,
	sge::d3d9::state::core::sampler::state_vector const &_states
)
:
	sge::renderer::state::core::sampler::object(),
	device_(
		_device
	),
	states_(
		_states
	)
{
}

sge::d3d9::state::core::sampler::object::~object()
{
}

void
sge::d3d9::state::core::sampler::object::set(
	sge::renderer::texture::stage const _stage
) const
{
	for(
		sge::d3d9::state::core::sampler::state_vector::const_iterator it(
			states_.begin()
		);
		it != states_.end();
		++it
	)
		sge::d3d9::devicefuncs::set_sampler_state(
			device_,
			_stage,
			it->type(),
			it->value()
		);
}
