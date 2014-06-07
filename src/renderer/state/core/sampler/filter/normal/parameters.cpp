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


#include <sge/renderer/state/core/sampler/filter/normal/mag.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/min.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/mip.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/parameters.hpp>


sge::renderer::state::core::sampler::filter::normal::parameters::parameters(
	sge::renderer::state::core::sampler::filter::normal::mag const _mag,
	sge::renderer::state::core::sampler::filter::normal::min const _min,
	sge::renderer::state::core::sampler::filter::normal::mip const _mip
)
:
	mag_(
		_mag
	),
	min_(
		_min
	),
	mip_(
		_mip
	)
{
}

sge::renderer::state::core::sampler::filter::normal::mag
sge::renderer::state::core::sampler::filter::normal::parameters::mag() const
{
	return mag_;
}

sge::renderer::state::core::sampler::filter::normal::min
sge::renderer::state::core::sampler::filter::normal::parameters::min() const
{
	return min_;
}

sge::renderer::state::core::sampler::filter::normal::mip
sge::renderer::state::core::sampler::filter::normal::parameters::mip() const
{
	return mip_;
}

bool
sge::renderer::state::core::sampler::filter::normal::operator==(
	sge::renderer::state::core::sampler::filter::normal::parameters const &_left,
	sge::renderer::state::core::sampler::filter::normal::parameters const &_right
)
{
	return
		_left.mag() == _right.mag()
		&& _left.min() == _right.min()
		&& _left.mip() == _right.mip();
}
