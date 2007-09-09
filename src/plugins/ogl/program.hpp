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


#ifndef SGE_OGL_PROGRAM_HPP_INCLUDED
#define SGE_OGL_PROGRAM_HPP_INCLUDED

#include <vector>
#include <boost/noncopyable.hpp>
#include "common.hpp"
#include "shader.hpp"
#include "uniform_variable.hpp"
#include "attribute_variable.hpp"

namespace sge
{
namespace ogl
{

class program : boost::noncopyable {
public:
	program();
	~program();
	void attach_shader(shader_ptr shader);
	void link();
	void use();
	uniform_variable uniform(const std::string&);
	attribute_variable attribute(const std::string&);
private:
	GLuint id() const;

	typedef std::vector<shader_ptr> shader_vector;
	shader_vector                   shaders;
	GLuint                          id_;
};

}
}

#endif
