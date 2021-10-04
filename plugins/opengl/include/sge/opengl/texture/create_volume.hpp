//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_CREATE_VOLUME_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_CREATE_VOLUME_HPP_INCLUDED

#include <sge/opengl/texture/basic_parameters_fwd.hpp>
#include <sge/renderer/texture/volume_parameters_fwd.hpp>
#include <sge/renderer/texture/volume_unique_ptr.hpp>


namespace sge::opengl::texture
{

sge::renderer::texture::volume_unique_ptr
create_volume(
	sge::opengl::texture::basic_parameters const &,
	sge::renderer::texture::volume_parameters const &
);

}

#endif
