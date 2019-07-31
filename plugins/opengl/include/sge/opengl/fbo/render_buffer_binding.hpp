//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_FBO_RENDER_BUFFER_BINDING_HPP_INCLUDED
#define SGE_OPENGL_FBO_RENDER_BUFFER_BINDING_HPP_INCLUDED

#include <sge/opengl/fbo/attachment.hpp>
#include <sge/opengl/fbo/attachment_type.hpp>
#include <sge/opengl/fbo/config_fwd.hpp>
#include <sge/opengl/fbo/render_buffer_binding_fwd.hpp>
#include <sge/opengl/fbo/render_buffer_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace fbo
{

class render_buffer_binding
:
	public sge::opengl::fbo::attachment
{
	FCPPT_NONCOPYABLE(
		render_buffer_binding
	);
public:
	render_buffer_binding(
		sge::opengl::fbo::config const &,
		sge::opengl::fbo::render_buffer const &,
		sge::opengl::fbo::attachment_type
	);

	~render_buffer_binding()
	override;
private:
	sge::opengl::fbo::config const &context_;

	sge::opengl::fbo::attachment_type const what_;
};

}
}
}

#endif
