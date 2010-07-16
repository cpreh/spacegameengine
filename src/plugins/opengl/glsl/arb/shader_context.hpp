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


#ifndef SGE_OPENGL_GLSL_ARB_SHADER_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_GLSL_ARB_SHADER_CONTEXT_HPP_INCLUDED

#include "handle.hpp"
#include "../shader_type.hpp"
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
namespace arb
{

struct shader_context
:
	public opengl::context::base
{
	FCPPT_NONCOPYABLE(shader_context)
public:
	shader_context();

	~shader_context();

	typedef arb::handle handle;

	typedef handle (*gl_create_shader);

	typedef void (*gl_delete_shader)(handle);

	gl_create_shader
	create_shader() const;
	
	gl_delete_shader
	delete_shader() const;

	GLenum
	make_shader_type(
		glsl::shader_type::type
	) const;

	typedef void needs_before;

	static opengl::context::id const static_id;
private:
	gl_create_shader const create_shader_;

	gl_delete_shader const delete_shader_;
};

}
}
}
}

#endif
