//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TEXTURE_FUNCS_BIND_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_FUNCS_BIND_HPP_INCLUDED

#include <sge/opengl/texture/optional_id.hpp>
#include <sge/opengl/texture/type.hpp>

namespace sge::opengl::texture::funcs
{

void bind(sge::opengl::texture::type, sge::opengl::texture::optional_id const &);

}

#endif
