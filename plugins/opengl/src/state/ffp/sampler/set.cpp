//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/state/ffp/sampler/context.hpp>
#include <sge/opengl/state/ffp/sampler/default_context.hpp>
#include <sge/opengl/state/ffp/sampler/object.hpp>
#include <sge/opengl/state/ffp/sampler/set.hpp>
#include <sge/opengl/texture/active_level.hpp>
#include <sge/renderer/state/ffp/sampler/const_object_ref_vector.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/make_int_range.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/make_literal_strong_typedef.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/cast/static_downcast.hpp>
#include <fcppt/log/object_fwd.hpp>


void
sge::opengl::state::ffp::sampler::set(
	fcppt::log::object &_log,
	sge::opengl::context::object &_context,
	sge::renderer::state::ffp::sampler::const_object_ref_vector const &_samplers
)
{
	sge::renderer::texture::stage const count(
		fcppt::strong_typedef_construct_cast<
			sge::renderer::texture::stage,
			fcppt::cast::size_fun
		>(
			_samplers.size()
		)
	);

	for(
		sge::renderer::texture::stage const stage
		:
		fcppt::make_int_range_count(
			count
		)
	)
	{
		sge::opengl::texture::active_level const active_level(
			_log,
			_context,
			stage
		);

		fcppt::cast::static_downcast<
			sge::opengl::state::ffp::sampler::object const &
		>(
			_samplers[
				stage.get()
			].get()
		).set(
			active_level
		);
	}

	sge::opengl::state::ffp::sampler::object const &default_state(
		sge::opengl::context::use<
			sge::opengl::state::ffp::sampler::default_context
		>(
			_context
		).default_state()
	);

	sge::opengl::state::ffp::sampler::context &context(
		sge::opengl::context::use<
			sge::opengl::state::ffp::sampler::context
		>(
			_context
		)
	);

	for(
		sge::renderer::texture::stage const stage
		:
		fcppt::make_int_range(
			count,
			context.stages()
		)
	)
	{
		sge::opengl::texture::active_level const active_level(
			_log,
			_context,
			stage
		);

		default_state.set(
			active_level
		);
	}

	context.stages(
		count
	);
}
