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


#ifndef SGE_RENDERER_GLSL_VERTEX_SHADER_HPP_INCLUDED
#define SGE_RENDERER_GLSL_VERTEX_SHADER_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/glsl/shader.hpp>
#include <sge/renderer/glsl/vertex_shader_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace glsl
{

/**
 * \brief A vertex shader used to transform vertices
 *
 * Vertex shaders can be used to transform vertices when they are rendered.
*/
class SGE_CLASS_SYMBOL vertex_shader
:
	public glsl::shader
{
	FCPPT_NONCOPYABLE(
		vertex_shader
	);
protected:
	SGE_RENDERER_SYMBOL
	vertex_shader();
public:
	SGE_RENDERER_SYMBOL
	virtual ~vertex_shader() = 0;
};

}
}
}

#endif
