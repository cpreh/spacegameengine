//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_FFP_CLIP_PLANE_OBJECT_FWD_HPP_INCLUDED
#define SGE_OPENGL_STATE_FFP_CLIP_PLANE_OBJECT_FWD_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/state/unary_object_fwd.hpp>
#include <sge/renderer/state/ffp/clip_plane/object_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace state
{
namespace ffp
{
namespace clip_plane
{

using
object
=
sge::opengl::state::unary_object<
	sge::renderer::state::ffp::clip_plane::object,
	GLenum
>;

}
}
}
}
}

#endif
