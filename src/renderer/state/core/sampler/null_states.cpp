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


#include <sge/renderer/state/core/sampler/const_object_ref_map.hpp>
#include <sge/renderer/state/core/sampler/const_optional_object_ref.hpp>
#include <sge/renderer/state/core/sampler/const_optional_object_ref_map.hpp>
#include <sge/src/renderer/state/core/sampler/null_states.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::renderer::state::core::sampler::const_optional_object_ref_map const
sge::renderer::state::core::sampler::null_states(
	sge::renderer::state::core::sampler::const_object_ref_map const &_map
)
{
	sge::renderer::state::core::sampler::const_optional_object_ref_map result;

	for(
		sge::renderer::state::core::sampler::const_object_ref_map::const_iterator it(
			_map.begin()
		);
		it != _map.end();
		++it
	)
		result.insert(
			std::make_pair(
				it->first,
				sge::renderer::state::core::sampler::const_optional_object_ref()
			)
		);

	return result;
}
