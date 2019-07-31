//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_VF_CLIENT_STATE_COMBINER_HPP_INCLUDED
#define SGE_OPENGL_VF_CLIENT_STATE_COMBINER_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/vf/attribute_context_fwd.hpp>
#include <sge/opengl/vf/client_state.hpp>
#include <sge/opengl/vf/client_state_combiner_fwd.hpp>
#include <sge/opengl/vf/context_fwd.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace vf
{

class client_state_combiner
{
	FCPPT_NONCOPYABLE(
		client_state_combiner
	);
public:
	client_state_combiner(
		fcppt::log::object &,
		sge::opengl::context::object &
	);

	void
	enable(
		GLenum
	);

	void
	disable(
		GLenum
	);

	void
	enable_texture(
		sge::renderer::texture::stage
	);

	void
	disable_texture(
		sge::renderer::texture::stage
	);

	void
	enable_attribute(
		GLuint
	);

	void
	disable_attribute(
		GLuint
	);

	~client_state_combiner();
private:
	fcppt::log::object &log_;

	sge::opengl::context::object &context_;

	sge::opengl::vf::context &vf_context_;

	sge::opengl::vf::attribute_context &attribute_context_;

	sge::opengl::vf::client_state const old_states_;

	sge::opengl::vf::client_state new_states_;
};

}
}
}

#endif
