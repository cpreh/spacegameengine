//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/state/convert/light_index.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/state/index_count.hpp>

GLenum sge::opengl::state::convert::light_index(sge::renderer::state::index_count const _index)
{
  return GL_LIGHT0 + _index;
}
