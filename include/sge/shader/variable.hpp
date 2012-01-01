/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SHADER_VARIABLE_HPP_INCLUDED
#define SGE_SHADER_VARIABLE_HPP_INCLUDED

#include <sge/renderer/glsl/string.hpp>
#include <sge/shader/symbol.hpp>
#include <sge/shader/value_variant.hpp>
#include <sge/shader/variable_type.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>


namespace sge
{
namespace shader
{
class variable
{
public:
	SGE_SHADER_SYMBOL explicit
	variable(
		renderer::glsl::string const &name,
		shader::variable_type::type,
		shader::value_variant const &);

	SGE_SHADER_SYMBOL renderer::glsl::string const
	declaration() const;

	SGE_SHADER_SYMBOL shader::variable_type::type
	type() const;

	SGE_SHADER_SYMBOL renderer::glsl::string const
	name() const;

	SGE_SHADER_SYMBOL shader::value_variant const
	initial_value() const;
private:
	renderer::glsl::string name_,declaration_;
	shader::variable_type::type type_;
	shader::value_variant initial_value_;
};
}
}

#endif
