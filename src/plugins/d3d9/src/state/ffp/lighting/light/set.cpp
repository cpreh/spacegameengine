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
#include <sge/d3d9/devicefuncs/light_enable.hpp>
#include <sge/d3d9/state/ffp/lighting/light/object.hpp>
#include <sge/d3d9/state/ffp/lighting/light/set.hpp>
#include <sge/renderer/caps/light_indices.hpp>
#include <sge/renderer/state/index_count.hpp>
#include <sge/renderer/state/ffp/lighting/light/const_object_ref_vector.hpp>


void
sge::d3d9::state::ffp::lighting::light::set(
	IDirect3DDevice9 &_device,
	sge::renderer::state::ffp::lighting::light::const_object_ref_vector const &_lights,
	sge::renderer::caps::light_indices const _max_lights
)
{
	sge::renderer::state::index_count index(
		0u
	);

	for(
		sge::renderer::state::ffp::lighting::light::const_object_ref_vector::const_iterator it(
			_lights.begin()
		);
		it != _lights.end();
		++it, ++index
	)
	{
		static_cast<
			sge::d3d9::state::ffp::lighting::light::object const &
		>(
			it->get()
		).set(
			index
		);

		sge::d3d9::devicefuncs::light_enable(
			_device,
			index,
			true
		);
	}

	for(
		;
		index < _max_lights.get();
		++index
	)
		sge::d3d9::devicefuncs::light_enable(
			_device,
			index,
			false
		);
}
