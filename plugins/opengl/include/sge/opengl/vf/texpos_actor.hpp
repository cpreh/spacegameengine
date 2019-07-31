//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_VF_TEXPOS_ACTOR_HPP_INCLUDED
#define SGE_OPENGL_VF_TEXPOS_ACTOR_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/vf/actor_parameters_fwd.hpp>
#include <sge/opengl/vf/pointer.hpp>
#include <sge/opengl/vf/pointer_actor.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <sge/renderer/vf/dynamic/texpos_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace vf
{

class texpos_actor
:
	public sge::opengl::vf::pointer_actor
{
	FCPPT_NONCOPYABLE(
		texpos_actor
	);
public:
	texpos_actor(
		fcppt::log::object &,
		sge::opengl::vf::actor_parameters const &,
		sge::renderer::vf::dynamic::texpos const &
	);

	~texpos_actor()
	override;
private:
	void
	operator()(
		sge::opengl::vf::client_state_combiner &,
		sge::opengl::vf::pointer
	) const
	override;

	void
	unuse(
		sge::opengl::vf::client_state_combiner &
	) const
	override;

	fcppt::log::object &log_;

	sge::opengl::context::object &context_;

	GLint const elements_;

	GLenum const format_;

	sge::renderer::texture::stage const index_;
};

}
}
}

#endif
