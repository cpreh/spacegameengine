//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TEXTURE_CREATE_LOCK_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_CREATE_LOCK_HPP_INCLUDED

#include <sge/opengl/buffer/stride.hpp>
#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/texture/lock_base_unique_ptr.hpp>
#include <sge/opengl/texture/read_size.hpp>
#include <sge/opengl/texture/write_size.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/lock_flags/method_fwd.hpp>

namespace sge::opengl::texture
{

sge::opengl::texture::lock_base_unique_ptr create_lock(
    sge::opengl::context::object_ref,
    sge::renderer::lock_flags::method,
    sge::opengl::texture::read_size,
    sge::opengl::texture::write_size,
    sge::opengl::buffer::stride,
    sge::renderer::resource_flags_field const &);

}

#endif
