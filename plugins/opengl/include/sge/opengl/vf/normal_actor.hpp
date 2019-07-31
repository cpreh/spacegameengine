//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_VF_NORMAL_ACTOR_HPP_INCLUDED
#define SGE_OPENGL_VF_NORMAL_ACTOR_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/vf/actor_parameters_fwd.hpp>
#include <sge/opengl/vf/fp_actor.hpp>
#include <sge/opengl/vf/pointer.hpp>
#include <sge/renderer/vf/dynamic/normal_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace vf
{

class normal_actor
:
	public sge::opengl::vf::fp_actor
{
	FCPPT_NONCOPYABLE(
		normal_actor
	);
public:
	normal_actor(
		sge::opengl::vf::actor_parameters const &,
		sge::renderer::vf::dynamic::normal const &
	);

	~normal_actor()
	override;
private:
	void
	on_use(
		sge::opengl::vf::pointer
	) const
	override;

	GLenum const format_;
};

}
}
}

#endif
