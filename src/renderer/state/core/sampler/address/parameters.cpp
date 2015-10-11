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


#include <sge/renderer/state/core/sampler/address/mode_s.hpp>
#include <sge/renderer/state/core/sampler/address/mode_t.hpp>
#include <sge/renderer/state/core/sampler/address/mode_u.hpp>
#include <sge/renderer/state/core/sampler/address/parameters.hpp>


sge::renderer::state::core::sampler::address::parameters::parameters(
	sge::renderer::state::core::sampler::address::mode_s const _mode_s,
	sge::renderer::state::core::sampler::address::mode_t const _mode_t,
	sge::renderer::state::core::sampler::address::mode_u const _mode_u
)
:
	mode_s_(
		_mode_s
	),
	mode_t_(
		_mode_t
	),
	mode_u_(
		_mode_u
	)
{
}

sge::renderer::state::core::sampler::address::mode_s
sge::renderer::state::core::sampler::address::parameters::mode_s() const
{
	return
		mode_s_;
}

sge::renderer::state::core::sampler::address::mode_t
sge::renderer::state::core::sampler::address::parameters::mode_t() const
{
	return
		mode_t_;
}

sge::renderer::state::core::sampler::address::mode_u
sge::renderer::state::core::sampler::address::parameters::mode_u() const
{
	return
		mode_u_;
}

bool
sge::renderer::state::core::sampler::address::operator==(
	sge::renderer::state::core::sampler::address::parameters const &_left,
	sge::renderer::state::core::sampler::address::parameters const &_right
)
{
	return
		_left.mode_s() == _right.mode_s()
		&&
		_left.mode_t() == _right.mode_t()
		&&
		_left.mode_u() == _right.mode_u()
		;
}
