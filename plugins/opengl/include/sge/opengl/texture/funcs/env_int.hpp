//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TEXTURE_FUNCS_ENV_INT_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_FUNCS_ENV_INT_HPP_INCLUDED

#include <sge/opengl/texture/active_level_fwd.hpp>
#include <sge/opengl/texture/funcs/env_arg.hpp>
#include <sge/opengl/texture/funcs/env_int_value.hpp>
#include <sge/opengl/texture/funcs/env_target.hpp>

namespace sge::opengl::texture::funcs
{

void env_int(
    sge::opengl::texture::active_level const &,
    sge::opengl::texture::funcs::env_target,
    sge::opengl::texture::funcs::env_arg,
    sge::opengl::texture::funcs::env_int_value);

}

#endif
