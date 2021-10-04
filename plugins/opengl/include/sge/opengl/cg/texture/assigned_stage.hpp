//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_CG_TEXTURE_ASSIGNED_STAGE_HPP_INCLUDED
#define SGE_OPENGL_CG_TEXTURE_ASSIGNED_STAGE_HPP_INCLUDED

#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/renderer/texture/stage.hpp>


namespace sge::opengl::cg::texture
{

sge::renderer::texture::stage
assigned_stage(
	sge::cg::parameter::object const &
);

}

#endif
