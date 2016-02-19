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


#include <sge/d3d9/state/core/sampler/object.hpp>
#include <sge/d3d9/state/core/sampler/set.hpp>
#include <sge/renderer/state/core/sampler/const_optional_object_ref_map.hpp>
#include <sge/renderer/state/core/sampler/object.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/cast/static_downcast.hpp>


void
sge::d3d9::state::core::sampler::set(
	sge::renderer::state::core::sampler::const_optional_object_ref_map const &_states,
	sge::d3d9::state::core::sampler::object const &_default
)
{
	for(
		auto const &sampler
		:
		_states
	)
		fcppt::optional::maybe(
			sampler.second,
			[
				&_default
			]()
			{
				return
					fcppt::make_cref(
						_default
					);
			},
			[](
				fcppt::reference<
					sge::renderer::state::core::sampler::object const
				> const _ref
			)
			{
				return
					fcppt::make_cref(
						fcppt::cast::static_downcast<
							sge::d3d9::state::core::sampler::object const &
						>(
							_ref.get()
						)
					);
			}
		).get().set(
			sampler.first
		);
}
