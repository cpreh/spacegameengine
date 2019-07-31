//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_CREATE_LOCK_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_CREATE_LOCK_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/texture/lock_base.hpp>
#include <sge/opengl/texture/lock_base_unique_ptr.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/lock_flags/method_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

sge::opengl::texture::lock_base_unique_ptr
create_lock(
	sge::opengl::context::object &,
	sge::renderer::lock_flags::method,
	sge::opengl::texture::lock_base::size_type read_size,
	sge::opengl::texture::lock_base::size_type write_size,
	sge::opengl::texture::lock_base::size_type stride,
	sge::renderer::resource_flags_field const &
);

}
}
}

#endif
