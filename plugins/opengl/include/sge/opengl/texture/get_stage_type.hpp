//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_GET_STAGE_TYPE_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_GET_STAGE_TYPE_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/texture/optional_type_fwd.hpp>
#include <sge/renderer/texture/stage.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

sge::opengl::texture::optional_type
get_stage_type(
	sge::opengl::context::object &,
	sge::renderer::texture::stage
);

}
}
}

#endif
