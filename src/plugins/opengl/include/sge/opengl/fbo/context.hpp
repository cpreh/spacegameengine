/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_OPENGL_FBO_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_FBO_CONTEXT_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <sge/opengl/fbo/context_config.hpp>
#include <sge/opengl/fbo/context_fwd.hpp>
#include <sge/opengl/fbo/error_string_map.hpp>
#include <sge/opengl/fbo/optional_attachment_type.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>


namespace sge
{
namespace opengl
{
namespace fbo
{

class context
:
	public sge::opengl::context::system::base
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	context();

	~context();

	bool
	is_supported() const;

	typedef PFNGLGENFRAMEBUFFERSPROC gl_gen_framebuffers;

	typedef PFNGLDELETEFRAMEBUFFERSPROC gl_delete_framebuffers;

	typedef PFNGLBINDFRAMEBUFFERPROC gl_bind_framebuffer;

	typedef PFNGLFRAMEBUFFERTEXTURE2DPROC gl_framebuffer_texture_2d;

	typedef PFNGLCHECKFRAMEBUFFERSTATUSPROC gl_check_framebuffer_status;

	typedef PFNGLGENRENDERBUFFERSPROC gl_gen_renderbuffers;

	typedef PFNGLDELETERENDERBUFFERSPROC gl_delete_renderbuffers;

	typedef PFNGLBINDRENDERBUFFERPROC gl_bind_renderbuffer;

	typedef PFNGLRENDERBUFFERSTORAGEPROC gl_renderbuffer_storage;

	typedef PFNGLFRAMEBUFFERRENDERBUFFERPROC gl_framebuffer_renderbuffer;

	gl_gen_framebuffers
	gen_framebuffers() const;

	gl_delete_framebuffers
	delete_framebuffers() const;

	gl_bind_framebuffer
	bind_framebuffer() const;

	gl_framebuffer_texture_2d
	framebuffer_texture_2d() const;

	gl_check_framebuffer_status
	check_framebuffer_status() const;

	gl_gen_renderbuffers
	gen_renderbuffers() const;

	gl_delete_renderbuffers
	delete_renderbuffers() const;

	gl_bind_renderbuffer
	bind_renderbuffer() const;

	gl_renderbuffer_storage
	renderbuffer_storage() const;

	gl_framebuffer_renderbuffer
	framebuffer_renderbuffer() const;

	GLenum
	framebuffer_target() const;

	sge::opengl::fbo::attachment_type const
	color_attachment() const;

	GLenum
	framebuffer_complete() const;

	sge::opengl::fbo::error_string_map const &
	error_strings() const;

	GLenum
	renderbuffer_target() const;

	sge::opengl::fbo::attachment_type const
	depth_attachment() const;

	sge::opengl::fbo::optional_attachment_type const
	depth_stencil_attachment() const;

	typedef void parameter;

	static sge::opengl::context::system::id const static_id;
private:
	typedef fcppt::optional<
		sge::opengl::fbo::context_config
	> optional_context_config;

	optional_context_config config_;
};

}
}
}

#endif
