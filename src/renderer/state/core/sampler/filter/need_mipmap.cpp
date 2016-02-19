/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/renderer/state/core/sampler/filter/need_mipmap.hpp>
#include <sge/renderer/state/core/sampler/filter/parameters.hpp>
#include <sge/renderer/state/core/sampler/filter/anisotropic/mip.hpp>
#include <sge/renderer/state/core/sampler/filter/anisotropic/parameters.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/mip.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/parameters.hpp>
#include <fcppt/variant/match.hpp>


bool
sge::renderer::state::core::sampler::filter::need_mipmap(
	sge::renderer::state::core::sampler::filter::parameters const &_filter
)
{
	return
		fcppt::variant::match(
			_filter.variant(),
			[](
				sge::renderer::state::core::sampler::filter::anisotropic::parameters const &_parameters
			)
			{
				return
					_parameters.mip()
					!=
					sge::renderer::state::core::sampler::filter::anisotropic::mip::off;
			},
			[](
				sge::renderer::state::core::sampler::filter::normal::parameters const &_parameters
			)
			{
				return
					_parameters.mip()
					!=
					sge::renderer::state::core::sampler::filter::normal::mip::off;
			}
		);
}
