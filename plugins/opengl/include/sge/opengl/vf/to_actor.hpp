//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_VF_TO_ACTOR_HPP_INCLUDED
#define SGE_OPENGL_VF_TO_ACTOR_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/vf/actor_unique_ptr.hpp>
#include <sge/renderer/vf/dynamic/ordered_element_fwd.hpp>
#include <sge/renderer/vf/dynamic/stride.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace vf
{

sge::opengl::vf::actor_unique_ptr
to_actor(
	fcppt::log::object &,
	sge::renderer::vf::dynamic::ordered_element const &,
	sge::renderer::vf::dynamic::stride,
	sge::opengl::context::object &
);

}
}
}

#endif
