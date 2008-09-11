/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_GLSL_PROGRAM_HPP_INCLUDED
#define SGE_OPENGL_GLSL_PROGRAM_HPP_INCLUDED

#include "../common.hpp"
#include "shader.hpp"
#include "uniform_variable.hpp"
#include "attribute_variable.hpp"
#include "traits.hpp"
#include <sge/shared_ptr.hpp>
#include <sge/renderer/glsl/program.hpp>
#include <sge/renderer/glsl/string.hpp>
#include <vector>

namespace sge
{
namespace ogl
{
namespace glsl
{

template<bool Native>
class program : public renderer::glsl::program {
public:
	typedef typename traits<Native>::handle handle;
	typedef typename shader<Native>::shared_ptr shader_ptr;

	program(
		renderer::glsl::string const &vs_source,
		renderer::glsl::string const &ps_source);
	~program();
	static void use(renderer::glsl::program_ptr);
private:
	renderer::glsl::uniform_variable_ptr const
	uniform(
		renderer::glsl::string const&);
	
	renderer::glsl::attribute_variable_ptr const
	attribute(
		renderer::glsl::string const&);
	
	static void use_ffp();
	void use();
	void attach_shader(
		shader_ptr shader);
	void link();
	handle id() const;

	typedef std::vector<shader_ptr> shader_vector;
	shader_vector                   shaders;
	GLuint                          id_;
};

}
}
}

#endif
