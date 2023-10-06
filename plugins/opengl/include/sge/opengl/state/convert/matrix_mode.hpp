//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_STATE_CONVERT_MATRIX_MODE_HPP_INCLUDED
#define SGE_OPENGL_STATE_CONVERT_MATRIX_MODE_HPP_INCLUDED

#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/state/ffp/transform/mode_fwd.hpp>

namespace sge::opengl::state::convert
{

GLenum matrix_mode(sge::renderer::state::ffp::transform::mode);

}

#endif
