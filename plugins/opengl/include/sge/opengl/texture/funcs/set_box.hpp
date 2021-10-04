//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_FUNCS_SET_BOX_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_FUNCS_SET_BOX_HPP_INCLUDED

#include <sge/opengl/color_base_type.hpp>
#include <sge/opengl/color_order.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/opengl/texture/volume_config_fwd.hpp>
#include <sge/renderer/const_raw_pointer.hpp>
#include <sge/renderer/dim3_fwd.hpp>
#include <sge/renderer/lock_box_fwd.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>


namespace sge::opengl::texture::funcs
{

void
set_box(
	sge::opengl::texture::binding const &,
	sge::opengl::context::object &, // NOLINT(google-runtime-references)
	sge::opengl::texture::volume_config const &,
	sge::opengl::texture::buffer_type,
	sge::opengl::color_order,
	sge::opengl::color_base_type,
	sge::renderer::texture::mipmap::level,
	sge::renderer::dim3 const &,
	sge::renderer::lock_box const &,
	sge::renderer::const_raw_pointer src
);

}

#endif
