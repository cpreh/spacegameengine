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


#include <sge/renderer/state/core/sampler/address/mode.hpp>
#include <sge/renderer/state/core/sampler/address/mode_all.hpp>
#include <sge/renderer/state/core/sampler/address/mode_s.hpp>
#include <sge/renderer/state/core/sampler/address/mode_t.hpp>
#include <sge/renderer/state/core/sampler/address/mode_u.hpp>
#include <sge/renderer/state/core/sampler/address/parameters.hpp>


sge::renderer::state::core::sampler::address::parameters const
sge::renderer::state::core::sampler::address::mode_all(
	sge::renderer::state::core::sampler::address::mode const _mode
)
{
	return
		sge::renderer::state::core::sampler::address::parameters(
			sge::renderer::state::core::sampler::address::mode_s(
				_mode
			),
			sge::renderer::state::core::sampler::address::mode_t(
				_mode
			),
			sge::renderer::state::core::sampler::address::mode_u(
				_mode
			)
		);
}
