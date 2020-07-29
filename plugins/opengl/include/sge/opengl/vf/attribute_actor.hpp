//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_VF_ATTRIBUTE_ACTOR_HPP_INCLUDED
#define SGE_OPENGL_VF_ATTRIBUTE_ACTOR_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/vf/actor_parameters_fwd.hpp>
#include <sge/opengl/vf/attribute_config_fwd.hpp>
#include <sge/opengl/vf/client_state_combiner_ref.hpp>
#include <sge/opengl/vf/pointer.hpp>
#include <sge/opengl/vf/pointer_actor.hpp>
#include <sge/renderer/vf/dynamic/extra_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_impl.hpp>


namespace sge
{
namespace opengl
{
namespace vf
{

class attribute_actor
:
	public sge::opengl::vf::pointer_actor
{
	FCPPT_NONMOVABLE(
		attribute_actor
	);
public:
	attribute_actor(
		sge::opengl::vf::actor_parameters const &,
		sge::renderer::vf::dynamic::extra const &
	);

	~attribute_actor()
	override;
private:
	void
	operator()(
		sge::opengl::vf::client_state_combiner_ref,
		sge::opengl::vf::pointer
	) const
	override;

	void
	unuse(
		sge::opengl::vf::client_state_combiner_ref
	) const
	override;

	fcppt::reference<
		sge::opengl::vf::attribute_config const
	> const attribute_config_;

	GLint const elements_;

	GLenum const format_;

	GLuint const location_;
};

}
}
}

#endif
