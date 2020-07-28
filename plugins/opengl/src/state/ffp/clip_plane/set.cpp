//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/state/set_array.hpp>
#include <sge/opengl/state/convert/clip_plane_index.hpp>
#include <sge/opengl/state/ffp/clip_plane/context.hpp>
#include <sge/opengl/state/ffp/clip_plane/object.hpp>
#include <sge/opengl/state/ffp/clip_plane/set.hpp>
#include <sge/renderer/state/ffp/clip_plane/const_object_ref_vector.hpp>
#include <fcppt/make_ref.hpp>


void
sge::opengl::state::ffp::clip_plane::set(
	sge::opengl::context::object &_context,
	sge::renderer::state::ffp::clip_plane::const_object_ref_vector const &_planes
)
{
	sge::opengl::state::set_array<
		sge::opengl::state::ffp::clip_plane::object
	>(
		sge::opengl::context::use<
			sge::opengl::state::ffp::clip_plane::context
		>(
			fcppt::make_ref(
				_context
			)
		),
		_planes,
		sge::opengl::state::convert::clip_plane_index
	);
}
