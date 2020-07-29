//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_MIPMAP_GENERATE_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_MIPMAP_GENERATE_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/type.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{
namespace mipmap
{

void
generate(
	sge::opengl::texture::binding const &,
	sge::opengl::context::object &, // NOLINT(google-runtime-references)
	sge::opengl::texture::type
);

}
}
}
}

#endif
