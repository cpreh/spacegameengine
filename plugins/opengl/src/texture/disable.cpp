//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/disable.hpp>
#include <sge/opengl/texture/active_level_fwd.hpp>
#include <sge/opengl/texture/disable.hpp>
#include <sge/opengl/texture/type.hpp>

void sge::opengl::texture::disable(
    sge::opengl::texture::active_level const &, sge::opengl::texture::type const _type)
{
  sge::opengl::disable(_type.get());
}
