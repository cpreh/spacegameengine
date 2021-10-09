//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/vf/extra_index.hpp>
#include <sge/renderer/vf/dynamic/index.hpp>

sge::renderer::vf::dynamic::index::value_type
sge::opengl::vf::extra_index(sge::renderer::vf::dynamic::index const _index)
{
  return
      // ATTR0 is special
      _index.get() + 1U;
}
