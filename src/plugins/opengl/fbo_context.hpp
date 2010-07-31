/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include "fbo_context_fwd.hpp"
#include "common.hpp"
#include "context/base.hpp"
#include "context/id.hpp"
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opengl
{

class fbo_context
:
	public opengl::context::base
{
	FCPPT_NONCOPYABLE(fbo_context)
public:
	fbo_context();

	~fbo_context();

	bool
	is_supported() const;

	typedef void (*gl_gen_framebuffers)(GLsizei, GLuint *);

	typedef void (*gl_delete_framebuffers)(GLsizei, GLuint *);

	typedef void (*gl_bind_framebuffer)(GLenum, GLuint);

	typedef void (*gl_framebuffer_texture_2d)(GLenum, GLenum, GLenum, GLuint, GLint);

	typedef GLenum (*gl_check_framebuffer_status)(GLenum);

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

	GLenum
	framebuffer_target() const;

	GLenum
	color_attachment() const;

	GLenum
	framebuffer_complete() const;

	typedef void needs_before;

	static context::id const static_id;
private:
	bool
		is_native_,
		is_ext_;
	
	gl_gen_framebuffers const gen_framebuffers_;

	gl_delete_framebuffers const delete_framebuffers_;

	gl_bind_framebuffer const bind_framebuffer_;

	GLenum const framebuffer_target_;
};

}
}

#endif
