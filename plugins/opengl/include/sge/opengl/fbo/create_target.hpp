//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_FBO_CREATE_TARGET_HPP_INCLUDED
#define SGE_OPENGL_FBO_CREATE_TARGET_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/renderer/target/offscreen_unique_ptr.hpp>


namespace sge
{
namespace opengl
{
namespace fbo
{

sge::renderer::target::offscreen_unique_ptr
create_target(
	sge::opengl::context::object &
);

}
}
}

#endif
