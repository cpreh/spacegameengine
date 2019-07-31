//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/vf/actor_parameters.hpp>
#include <sge/opengl/vf/pointer_actor.hpp>
#include <sge/renderer/vf/dynamic/offset.hpp>
#include <sge/renderer/vf/dynamic/stride.hpp>


sge::opengl::vf::pointer_actor::~pointer_actor()
{
}

sge::opengl::vf::pointer_actor::pointer_actor(
	sge::opengl::vf::actor_parameters const &_param
)
:
	offset_(
		_param.offset()
	),
	stride_(
		_param.stride()
	)
{
}

sge::renderer::vf::dynamic::offset
sge::opengl::vf::pointer_actor::offset() const
{
	return
		offset_;
}

sge::renderer::vf::dynamic::stride
sge::opengl::vf::pointer_actor::stride() const
{
	return
		stride_;
}
