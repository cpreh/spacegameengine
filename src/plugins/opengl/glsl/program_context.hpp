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


#ifndef SGE_OPENGL_GLSL_PROGRAM_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_GLSL_PROGRAM_CONTEXT_HPP_INCLUDED

#include "program_context_fwd.hpp"
#include "handle.hpp"
#include "context_fwd.hpp"
#include "../context/base.hpp"
#include "../common.hpp"
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opengl
{
namespace glsl
{

class program_context
:
	public opengl::context::base
{
	FCPPT_NONCOPYABLE(program_context)
public:
	explicit program_context(
		glsl::context &
	);

	~program_context();

	GLenum
	vertex_shader_type() const;

	GLenum
	pixel_shader_type() const;

	handle
	create_program() const;

	void
	delete_program(
		handle
	) const;

	void
	attach_shader(
		handle program,
		handle shader
	) const;

	void
	detach_shader(
		handle program,
		handle shader
	) const;

	void
	link_program(
		handle
	) const;

	GLint
	program_integer(
		GLenum,
		handle
	) const;

	GLint
	link_status(
		handle
	) const;

	void
	use_program(
		handle
	) const;

	void
	program_info_log(
		handle,
		GLint maxlen,
		GLint *len,
		char *data
	) const;

	GLint
	program_info_log_length(
		handle
	) const;
private:
	typedef handle (*gl_create_program)();

	typedef void (*gl_delete_program)(handle);

	gl_create_program const create_program_;

	gl_delete_program const delete_program_;
};
	
}
}
}

#endif
