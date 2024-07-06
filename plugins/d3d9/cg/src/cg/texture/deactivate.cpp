//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/cg/texture/deactivate.hpp>
#include <sge/d3d9/cg/texture/loaded_object.hpp>
#include <sge/renderer/cg/loaded_texture_fwd.hpp>

void sge::d3d9::cg::texture::deactivate(sge::renderer::cg::loaded_texture const &_texture)
{
  dynamic_cast<sge::d3d9::cg::texture::loaded_object const &>(_texture).deactivate();
}
