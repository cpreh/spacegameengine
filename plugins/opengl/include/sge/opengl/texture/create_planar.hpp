//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TEXTURE_CREATE_PLANAR_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_CREATE_PLANAR_HPP_INCLUDED

#include <sge/opengl/texture/basic_parameters_fwd.hpp>
#include <sge/renderer/texture/planar_parameters_fwd.hpp>
#include <sge/renderer/texture/planar_unique_ptr.hpp>

namespace sge::opengl::texture
{

sge::renderer::texture::planar_unique_ptr create_planar(
    sge::opengl::texture::basic_parameters const &,
    sge::renderer::texture::planar_parameters const &);

}

#endif
