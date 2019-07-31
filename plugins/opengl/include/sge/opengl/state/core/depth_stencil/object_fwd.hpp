//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_CORE_DEPTH_STENCIL_OBJECT_FWD_HPP_INCLUDED
#define SGE_OPENGL_STATE_CORE_DEPTH_STENCIL_OBJECT_FWD_HPP_INCLUDED

#include <sge/opengl/state/object_fwd.hpp>
#include <sge/renderer/state/core/depth_stencil/object_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace state
{
namespace core
{
namespace depth_stencil
{

typedef sge::opengl::state::object<
	sge::renderer::state::core::depth_stencil::object
> object;

}
}
}
}
}

#endif
