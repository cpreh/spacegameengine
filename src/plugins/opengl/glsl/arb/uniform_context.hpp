/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_GLSL_ARB_UNIFORM_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_GLSL_ARB_UNIFORM_CONTEXT_HPP_INCLUDED

#include "uniform_context_fwd.hpp"
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
namespace arb
{

class uniform_context
:
	public opengl::context::base
{
	FCPPT_NONCOPYABLE(uniform_context)
public:
	uniform_context();

	~uniform_context();

	typedef arb::handle handle;

	PFNGLGETUNIFORMLOCATIONARBPROC
	get_uniform_location() const;

	PFNGLGETUNIFORMIVARBPROC
	get_uniform_iv() const;

	PFNGLGETUNIFORMFVARBPROC
	get_uniform_fv() const;

	PFNGLUNIFORM1IVARBPROC
	uniform_1iv() const;

	PFNGLUNIFORM2IVARBPROC
	uniform_2iv() const;

	PFNGLUNIFORM3IVARBPROC
	uniform_3iv() const;

	PFNGLUNIFORM4IVARBPROC
	uniform_4iv() const;

	PFNGLUNIFORM1FVARBPROC
	uniform_1fv() const;

	PFNGLUNIFORM2FVARBPROC
	uniform_2fv() const;

	PFNGLUNIFORM3FVARBPROC
	uniform_3fv() const;

	PFNGLUNIFORM4FVARBPROC
	uniform_4fv() const;

	PFNGLUNIFORMMATRIX2FVARBPROC
	uniform_matrix_2fv() const;

	PFNGLUNIFORMMATRIX3FVARBPROC
	uniform_matrix_3fv() const;

	PFNGLUNIFORMMATRIX4FVARBPROC
	uniform_matrix_4fv() const;

	typedef void needs_before;

	static opengl::context::id const static_id;
private:
	PFNGLGETUNIFORMLOCATIONARBPROC const get_uniform_location_;
	
	PFNGLGETUNIFORMIVARBPROC const get_uniform_iv_;

	PFNGLGETUNIFORMFVARBPROC const get_uniform_fv_;

	PFNGLUNIFORM1IVARBPROC const uniform_1iv_;

	PFNGLUNIFORM2IVARBPROC const uniform_2iv_;

	PFNGLUNIFORM3IVARBPROC const uniform_3iv_;

	PFNGLUNIFORM4IVARBPROC const uniform_4iv_;

	PFNGLUNIFORM1FVARBPROC const uniform_1fv_;

	PFNGLUNIFORM2FVARBPROC const uniform_2fv_;

	PFNGLUNIFORM3FVARBPROC const uniform_3fv_;

	PFNGLUNIFORM4FVARBPROC const uniform_4fv_;

	PFNGLUNIFORMMATRIX2FVARBPROC const uniform_matrix_2fv_;

	PFNGLUNIFORMMATRIX3FVARBPROC const uniform_matrix_3fv_;

	PFNGLUNIFORMMATRIX4FVARBPROC const uniform_matrix_4fv_;
};

}
}
}
}

#endif
