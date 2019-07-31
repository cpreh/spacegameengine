//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_FBO_RENDER_BUFFER_HPP_INCLUDED
#define SGE_OPENGL_FBO_RENDER_BUFFER_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/internal_color_format.hpp>
#include <sge/opengl/fbo/config_fwd.hpp>
#include <sge/opengl/fbo/render_buffer_fwd.hpp>
#include <sge/opengl/fbo/render_buffer_holder.hpp>
#include <sge/renderer/dim2_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace fbo
{

class render_buffer
{
	FCPPT_NONCOPYABLE(
		render_buffer
	);
public:
	render_buffer(
		sge::opengl::fbo::config const &,
		sge::opengl::internal_color_format,
		sge::renderer::dim2 const &
	);

	~render_buffer();

	GLuint
	id() const;
private:
	void
	bind() const;

	sge::opengl::fbo::config const &context_;

	sge::opengl::fbo::render_buffer_holder const holder_;
};

}
}
}

#endif
