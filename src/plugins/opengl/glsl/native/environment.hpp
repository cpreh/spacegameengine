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


#ifndef SGE_OPENGL_GLSL_NATIVE_ENVIRONMENT_HPP_INCLUDED
#define SGE_OPENGL_GLSL_NATIVE_ENVIRONMENT_HPP_INCLUDED

#include "program_context_fwd.hpp"
#include "shader_context_fwd.hpp"
#include "uniform_context_fwd.hpp"
#include "handle.hpp"
#include <fcppt/restrict_typedef_struct.hpp>

namespace sge
{
namespace opengl
{
namespace glsl
{
namespace native
{

struct environment
{
	FCPPT_RESTRICT_TYPEDEF_STRUCT(
		environment
	);
public:
	typedef native::handle handle;

	typedef native::program_context program_context;

	typedef native::shader_context shader_context;

	typedef native::uniform_context uniform_context;
};

}
}
}
}

#endif
