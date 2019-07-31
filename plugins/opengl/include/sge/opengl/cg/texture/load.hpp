//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_CG_TEXTURE_LOAD_HPP_INCLUDED
#define SGE_OPENGL_CG_TEXTURE_LOAD_HPP_INCLUDED

#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/renderer/cg/loaded_texture_unique_ptr.hpp>
#include <sge/renderer/texture/base_fwd.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace cg
{
namespace texture
{

sge::renderer::cg::loaded_texture_unique_ptr
load(
	fcppt::log::object &,
	sge::opengl::context::object &,
	sge::cg::parameter::object const &,
	sge::renderer::texture::base &
);

}
}
}
}

#endif
