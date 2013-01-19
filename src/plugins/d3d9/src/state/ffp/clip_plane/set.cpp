/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/d3d9/devicefuncs/set_render_state.hpp>
#include <sge/d3d9/state/ffp/clip_plane/object.hpp>
#include <sge/d3d9/state/ffp/clip_plane/set.hpp>
#include <sge/renderer/state/index_count.hpp>
#include <sge/renderer/state/ffp/clip_plane/const_object_ref_vector.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>


void
sge::d3d9::state::ffp::clip_plane::set(
	IDirect3DDevice9 &_device,
	sge::renderer::state::ffp::clip_plane::const_object_ref_vector const &_states
)
{
	DWORD indices(
		0u
	);

	for(
		sge::renderer::state::ffp::clip_plane::const_object_ref_vector::const_iterator it(
			_states.begin()
		);
		it != _states.end();
		++it
	)
	{
		sge::renderer::state::index_count const index(
			static_cast<
				sge::renderer::state::index_count
			>(
				std::distance(
					it,
					_states.end()
				)
			)
		);

		static_cast<
			sge::d3d9::state::ffp::clip_plane::object const &
		>(
			it->get()
		).set(
			index
		);

		indices |= (1u << index);
	}

	sge::d3d9::devicefuncs::set_render_state(
		_device,
		D3DRS_CLIPPLANEENABLE,
		indices
	);
}
