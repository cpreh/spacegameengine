//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_FFP_CLIP_PLANE_SET_HPP_INCLUDED
#define SGE_OPENGL_STATE_FFP_CLIP_PLANE_SET_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/renderer/state/ffp/clip_plane/const_object_ref_vector.hpp>


namespace sge::opengl::state::ffp::clip_plane
{

void
set(
	sge::opengl::context::object &, // NOLINT(google-runtime-references)
	sge::renderer::state::ffp::clip_plane::const_object_ref_vector const &
);

}

#endif
