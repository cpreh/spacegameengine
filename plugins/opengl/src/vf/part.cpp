//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/common.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/vf/actor.hpp>
#include <sge/opengl/vf/client_state_combiner.hpp>
#include <sge/opengl/vf/part.hpp>
#include <sge/opengl/vf/pointer.hpp>
#include <sge/opengl/vf/to_actor.hpp>
#include <sge/renderer/vf/dynamic/ordered_element_fwd.hpp>
#include <sge/renderer/vf/dynamic/part.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/log/object_fwd.hpp>


sge::opengl::vf::part::part(
	fcppt::log::object &_log,
	sge::opengl::context::object &_context,
	sge::renderer::vf::dynamic::part const &_part
)
:
	log_{
		_log
	},
	context_(
		_context
	),
	part_(
		_part
	),
	actors_(
		fcppt::algorithm::map<
			actor_container
		>(
			_part.elements(),
			[
				&_log,
				&_part,
				&_context
			](
				sge::renderer::vf::dynamic::ordered_element const &_elem
			)
			{
				return
					sge::opengl::vf::to_actor(
						_log,
						_elem,
						_part.stride(),
						_context
					);
			}
		)
	)
{
}

sge::opengl::vf::part::~part()
{
}

sge::renderer::vf::dynamic::part const &
sge::opengl::vf::part::get() const
{
	return
		part_;
}

void
sge::opengl::vf::part::use_me(
	sge::opengl::vf::pointer const _src
) const
{
	sge::opengl::vf::client_state_combiner states(
		log_,
		context_
	);

	for(
		auto const &actor
		:
		actors_
	)
		(*actor)(
			states,
			fcppt::cast::from_void_ptr<
				unsigned char const *
			>(
				_src
			)
			+
			actor->offset().get()
		);
}

void
sge::opengl::vf::part::unuse_me() const
{
	sge::opengl::vf::client_state_combiner states(
		log_,
		context_
	);

	for(
		auto &actor
		:
		actors_
	)
		actor->unuse(
			states
		);
}
