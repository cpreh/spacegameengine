//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/state/core/sampler/context.hpp>
#include <sge/opengl/state/core/sampler/make_actors.hpp>
#include <sge/opengl/state/core/sampler/object.hpp>
#include <sge/renderer/state/core/sampler/const_object_ref.hpp>
#include <sge/renderer/state/core/sampler/const_optional_object_ref_map.hpp>
#include <sge/renderer/state/core/sampler/default.hpp>
#include <sge/renderer/state/core/sampler/object.hpp>
#include <sge/renderer/state/core/sampler/parameters.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/cast/static_downcast.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/optional/copy_value.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/join.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


sge::opengl::state::core::sampler::context::context(
	sge::opengl::state::core::sampler::context::parameter _context
)
:
	sge::opengl::context::base(),
	defaults_(
		fcppt::make_unique_ptr<
			sge::opengl::state::core::sampler::object
		>(
			sge::opengl::state::core::sampler::make_actors(
				_context,
				sge::renderer::state::core::sampler::default_()
			)
		)
	),
	objects_()
{
}

sge::opengl::state::core::sampler::context::~context()
= default;

void
sge::opengl::state::core::sampler::context::set(
	sge::renderer::state::core::sampler::const_optional_object_ref_map const &_samplers
)
{
	for(
		auto const &sampler
		:
		_samplers
	)
	{
		objects_[
			sampler.first
		] =
			fcppt::optional::map(
				sampler.second,
				[](
					sge::renderer::state::core::sampler::const_object_ref const &_sampler
				)
				->
				fcppt::reference<
					sge::opengl::state::core::sampler::object const
				>
				{
					return
						fcppt::make_cref(
							fcppt::cast::static_downcast<
								sge::opengl::state::core::sampler::object const &
							>(
								_sampler.get()
							)
						);
				}
			);
	}
}

sge::opengl::state::core::sampler::object const &
sge::opengl::state::core::sampler::context::get(
	sge::renderer::texture::stage const _stage
) const
{
	return
		fcppt::optional::from(
			fcppt::optional::join(
				fcppt::optional::copy_value(
					fcppt::container::find_opt_mapped(
						objects_,
						_stage
					)
				)
			),
			[
				this
			]()
			{
				return
					fcppt::make_cref(
						*defaults_
					);
			}
		).get();
}

void
sge::opengl::state::core::sampler::context::reset()
{
	objects_.clear();
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

sge::opengl::context::id const
sge::opengl::state::core::sampler::context::static_id(
	sge::opengl::context::make_id()
);

FCPPT_PP_POP_WARNING
