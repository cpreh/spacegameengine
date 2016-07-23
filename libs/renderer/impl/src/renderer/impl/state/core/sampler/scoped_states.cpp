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


#include <sge/renderer/impl/state/core/sampler/scoped_states.hpp>
#include <sge/renderer/state/core/sampler/const_object_ref_map.hpp>
#include <sge/renderer/state/core/sampler/const_optional_object_ref.hpp>
#include <sge/renderer/state/core/sampler/const_optional_object_ref_map.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::renderer::state::core::sampler::const_optional_object_ref_map
sge::renderer::impl::state::core::sampler::scoped_states(
	sge::renderer::state::core::sampler::const_object_ref_map const &_map
)
{
	return
		fcppt::algorithm::map<
			sge::renderer::state::core::sampler::const_optional_object_ref_map
		>(
			_map,
			[](
				sge::renderer::state::core::sampler::const_object_ref_map::value_type const &_element
			)
			{
				return
					std::make_pair(
						_element.first,
						sge::renderer::state::core::sampler::const_optional_object_ref(
							_element.second
						)
					);
			}
		);
}
