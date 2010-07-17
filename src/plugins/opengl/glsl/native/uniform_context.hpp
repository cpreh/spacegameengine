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


#ifndef SGE_OPENGL_GLSL_NATIVE_UNIFORM_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_GLSL_NATIVE_UNIFORM_CONTEXT_HPP_INCLUDED

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

class uniform_context
:
	public opengl::context::base
{
	FCPPT_NONCOPYABLE(uniform_context)
public:
	uniform_context();

	~uniform_context();

	typedef native::handle handle;

	PFNGLGETUNIFORMLOCATIONPROC
	get_uniform_location() const;

	PFNGLGETUNIFORMIVPROC
	get_uniform_iv() const;

	PFNGLGETUNIFORMFVPROC
	get_uniform_fv() const;

	PFNGLUNIFORM1IVPROC
	uniform_1iv() const;
	
	PFNGLUNIFORM2IVPROC
	uniform_2iv() const;

	PFNGLUNIFORM3IVPROC
	uniform_3iv() const;

	PFNGLUNIFORM4IVPROC
	uniform_4iv() const;

	PFNGLUNIFORM1FVPROC
	uniform_1fv() const;

	PFNGLUNIFORM2FVPROC
	uniform_2fv() const;

	PFNGLUNIFORM3FVPROC
	uniform_3fv() const;

	PFNGLUNIFORM3FVPROC
	uniform_4fv() const;

	PFNGLUNIFORMMATRIX2FVPROC
	uniform_matrix_2fv() const;
	
	PFNGLUNIFORMMATRIX3FVPROC
	uniform_matrix_3fv() const;

	PFNGLUNIFORMMATRIX4FVPROC
	uniform_matrix_4fv() const;

	PFNGLUNIFORMMATRIX2X3FVPROC
	uniform_matrix_2x3fv() const;

	PFNGLUNIFORMMATRIX3X2FVPROC
	uniform_matrix_3x2fv() const;

	PFNGLUNIFORMMATRIX2X4FVPROC
	uniform_matrix_2x4fv() const;

	PFNGLUNIFORMMATRIX4X2FVPROC
	uniform_matrix_4x2fv() const;

	PFNGLUNIFORMMATRIX3X4FVPROC
	uniform_matrix_3x4fv() const;

	PFNGLUNIFORMMATRIX4X3FVPROC
	uniform_matrix_4x3fv() const;

	typedef void needs_before;

	static opengl::context::id const static_id;
private:
	PFNGLGETUNIFORMLOCATIONPROC const get_uniform_location_;
	
	PFNGLGETUNIFORMIVPROC const get_uniform_iv_;

	PFNGLGETUNIFORMFVPROC const get_uniform_fv_;
};


}
}
}
}

#endif
