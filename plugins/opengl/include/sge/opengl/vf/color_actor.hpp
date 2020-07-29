//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_VF_COLOR_ACTOR_HPP_INCLUDED
#define SGE_OPENGL_VF_COLOR_ACTOR_HPP_INCLUDED

#include <sge/opengl/color_base_type.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/vf/actor_parameters_fwd.hpp>
#include <sge/opengl/vf/fp_actor.hpp>
#include <sge/opengl/vf/pointer.hpp>
#include <sge/renderer/vf/dynamic/color_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace opengl
{
namespace vf
{

class color_actor
:
	public sge::opengl::vf::fp_actor
{
	FCPPT_NONMOVABLE(
		color_actor
	);
public:
	color_actor(
		sge::opengl::vf::actor_parameters const &,
		sge::renderer::vf::dynamic::color const &
	);

	~color_actor()
	override;
private:
	void
	on_use(
		sge::opengl::vf::pointer
	) const
	override;

	GLint const elements_;

	sge::opengl::color_base_type const format_;
};

}
}
}

#endif
