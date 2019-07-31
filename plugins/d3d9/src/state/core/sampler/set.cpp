//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/state/core/sampler/object.hpp>
#include <sge/d3d9/state/core/sampler/set.hpp>
#include <sge/renderer/state/core/sampler/const_optional_object_ref_map.hpp>
#include <sge/renderer/state/core/sampler/object.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/cast/static_downcast.hpp>
#include <fcppt/optional/maybe.hpp>


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
