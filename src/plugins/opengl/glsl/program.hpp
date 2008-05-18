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
#include <sge/shared_ptr.hpp>
#include <sge/renderer/glsl_program.hpp>
#include <boost/noncopyable.hpp>
#include <vector>

namespace sge
{
namespace ogl
{
namespace glsl
{

template<typename Handle>
class program : public sge::glsl::program, boost::noncopyable {
public:
	typedef typename shader<Handle>::shared_ptr shader_ptr;
	program(
		std::string const &vs_source,
		std::string const &ps_source);
	~program();
	void attach_shader(
		shader_ptr shader);
	void link();
	void use();
	sge::glsl::uniform_variable_ptr uniform(
		const std::string&);
	sge::glsl::attribute_variable_ptr attribute(
		const std::string&);

	static void use_ffp();
private:
	Handle id() const;

	typedef std::vector<shader_ptr> shader_vector;
	shader_vector                   shaders;
	GLuint                          id_;
};

}
}
}

#endif
