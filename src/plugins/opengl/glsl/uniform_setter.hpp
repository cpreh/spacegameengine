/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_OPENGL_GLSL_UNIFORM_SETTER_HPP_INCLUDED
#define SGE_OPENGL_GLSL_UNIFORM_SETTER_HPP_INCLUDED

#include "traits.hpp"
#include "uniform_type.hpp"
#include <sge/renderer/glsl/int_type.hpp>
#include <sge/renderer/glsl/float_type.hpp>
#include <sge/renderer/glsl/uniform_matrix.hpp>
#include <sge/renderer/glsl/uniform_vector.hpp>
#include <sge/array_wrapper.hpp>
#include <boost/variant/static_visitor.hpp>

namespace sge
{
namespace ogl
{
namespace glsl
{

class uniform_setter : public boost::static_visitor<uniform_type::type> {
public:
	explicit uniform_setter(
		GLint location);
	
	uniform_type::type
	operator()(
		renderer::glsl::int_type) const;
	
	uniform_type::type
	operator()(
		renderer::glsl::float_type const &) const;

	uniform_type::type
	operator()(
		renderer::glsl::uniform_vector const &) const;
	
	uniform_type::type
	operator()(
		renderer::glsl::uniform_matrix const &) const;

	uniform_type::type
	operator()(
		array_wrapper<renderer::glsl::int_type> const &) const;
	
	uniform_type::type
	operator()(
		array_wrapper<renderer::glsl::float_type> const &) const;
		
	uniform_type::type
	operator()(
		array_wrapper<renderer::glsl::uniform_vector> const &) const;

	uniform_type::type
	operator()(
		array_wrapper<renderer::glsl::uniform_matrix> const &) const;
private:
	GLint const location;
};

}
}
}

#endif
