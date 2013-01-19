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
#include <sge/d3d9/state/set_defaults.hpp>
#include <sge/d3d9/state/core/defaults_fwd.hpp>
#include <sge/d3d9/state/core/set_defaults.hpp>
#include <sge/d3d9/state/ffp/defaults_fwd.hpp>
#include <sge/d3d9/state/ffp/set_defaults.hpp>
#include <sge/renderer/caps/light_indices.hpp>
#include <sge/renderer/caps/texture_stages.hpp>


void
sge::d3d9::state::set_defaults(
	IDirect3DDevice9 &_device,
	sge::d3d9::state::core::defaults const &_core_defaults,
	sge::d3d9::state::ffp::defaults const &_ffp_defaults,
	sge::renderer::caps::light_indices const _light_indices,
	sge::renderer::caps::texture_stages const _texture_stages
)
{
	sge::d3d9::state::core::set_defaults(
		_core_defaults,
		_texture_stages
	);

	sge::d3d9::state::ffp::set_defaults(
		_device,
		_ffp_defaults,
		_light_indices,
		_texture_stages
	);
}
