//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TEXTURE_SET_SAMPLERS_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_SET_SAMPLERS_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/texture/render_binding_fwd.hpp>

namespace sge::opengl::texture
{

void set_samplers(
    sge::opengl::texture::render_binding const &,
    sge::opengl::context::object & // NOLINT(google-runtime-references)
); // NOLINT(google-runtime-references)

}

#endif
