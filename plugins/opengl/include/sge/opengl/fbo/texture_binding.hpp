//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_FBO_TEXTURE_BINDING_HPP_INCLUDED
#define SGE_OPENGL_FBO_TEXTURE_BINDING_HPP_INCLUDED

#include <sge/opengl/fbo/attachment.hpp>
#include <sge/opengl/fbo/attachment_type.hpp>
#include <sge/opengl/fbo/config_fwd.hpp>
#include <sge/opengl/fbo/texture_binding_fwd.hpp>
#include <sge/opengl/texture/buffer_base_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace fbo
{

class texture_binding
:
	public fbo::attachment
{
	FCPPT_NONCOPYABLE(
		texture_binding
	);
public:
	texture_binding(
		sge::opengl::fbo::config const &,
		sge::opengl::texture::buffer_base &,
		sge::opengl::fbo::attachment_type
	);

	~texture_binding()
	override;
private:
	sge::opengl::fbo::config const &context_;

	sge::opengl::texture::buffer_base &buffer_;

	sge::opengl::fbo::attachment_type const attachment_;
};

}
}
}

#endif
