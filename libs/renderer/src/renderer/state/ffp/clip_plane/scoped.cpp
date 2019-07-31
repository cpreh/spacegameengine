//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/state/ffp/clip_plane/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/clip_plane/scoped.hpp>


sge::renderer::state::ffp::clip_plane::scoped::scoped(
	sge::renderer::context::ffp &_context,
	sge::renderer::state::ffp::clip_plane::const_object_ref_vector const &_states
)
:
	context_(
		_context
	)
{
	context_.clip_plane_state(
		_states
	);
}

sge::renderer::state::ffp::clip_plane::scoped::~scoped()
{
	context_.clip_plane_state(
		sge::renderer::state::ffp::clip_plane::const_object_ref_vector()
	);
}
