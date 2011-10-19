/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_GLSL_NATIVE_SHADER_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_GLSL_NATIVE_SHADER_CONTEXT_HPP_INCLUDED

#include "shader_context_fwd.hpp"
#include "handle.hpp"
#include "../../common.hpp"
#include "../../context/base.hpp"
#include "../../context/id.hpp"
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opengl
{
namespace glsl
{
namespace native
{

class shader_context
:
	public opengl::context::base
{
	FCPPT_NONCOPYABLE(
		shader_context
	);
public:
	shader_context();

	~shader_context();

	typedef native::handle handle;

	typedef PFNGLCREATESHADERPROC gl_create_shader;

	typedef PFNGLDELETESHADERPROC gl_delete_shader;

	typedef PFNGLCOMPILESHADERPROC gl_compile_shader;

	typedef PFNGLSHADERSOURCEPROC gl_shader_source;

	typedef PFNGLGETSHADERIVPROC gl_shader_integer;

	typedef PFNGLGETSHADERINFOLOGPROC gl_shader_info_log;

	typedef PFNGLGETSHADERSOURCEPROC gl_get_shader_source;

	gl_create_shader
	create_shader() const;

	gl_delete_shader
	delete_shader() const;

	gl_compile_shader
	compile_shader() const;

	gl_shader_source
	shader_source() const;

	gl_shader_integer
	shader_integer() const;

	gl_shader_info_log
	shader_info_log() const;

	gl_get_shader_source
	get_shader_source() const;

	GLenum
	vertex_shader_type() const;

	GLenum
	pixel_shader_type() const;

	GLenum
	geometry_shader_type() const;

	GLenum
	compile_status_type() const;

	GLenum
	info_log_length_type() const;

	GLenum
	source_length_type() const;

	typedef void needs_before;

	static opengl::context::id const static_id;
private:
	gl_create_shader const create_shader_;

	gl_delete_shader const delete_shader_;

	gl_compile_shader const compile_shader_;

	gl_shader_source const shader_source_;

	gl_shader_integer const shader_integer_;

	gl_shader_info_log const shader_info_log_;

	gl_get_shader_source const get_shader_source_;

	GLenum const
		vertex_shader_type_,
		pixel_shader_type_,
		geometry_shader_type_,
		compile_status_type_,
		info_log_length_type_,
		source_length_type_;
};

}
}
}
}

#endif
