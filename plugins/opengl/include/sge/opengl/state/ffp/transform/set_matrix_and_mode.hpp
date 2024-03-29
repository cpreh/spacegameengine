//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_STATE_FFP_TRANSFORM_SET_MATRIX_AND_MODE_HPP_INCLUDED
#define SGE_OPENGL_STATE_FFP_TRANSFORM_SET_MATRIX_AND_MODE_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/renderer/matrix4_fwd.hpp>
#include <sge/renderer/state/ffp/transform/mode_fwd.hpp>

namespace sge::opengl::state::ffp::transform
{

void set_matrix_and_mode(
    sge::opengl::context::object &, // NOLINT(google-runtime-references)
    sge::renderer::state::ffp::transform::mode,
    sge::renderer::matrix4 const &);

}

#endif
