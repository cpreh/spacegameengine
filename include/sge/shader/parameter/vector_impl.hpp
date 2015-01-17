/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SHADER_PARAMETER_VECTOR_IMPL_HPP_INCLUDED
#define SGE_SHADER_PARAMETER_VECTOR_IMPL_HPP_INCLUDED

#include <sge/cg/parameter/vector/set.hpp>
#include <sge/cg/program/object.hpp>
#include <sge/shader/parameter/name.hpp>
#include <sge/shader/parameter/vector_decl.hpp>
#include <fcppt/math/size_type.hpp>


template
<
	typename ValueType,
	fcppt::math::size_type N
>
sge::shader::parameter::vector<ValueType,N>::vector(
	sge::cg::program::object &_program,
	sge::shader::parameter::name const &_name,
	vector_type const &_initial_value)
:
	parameter_(
		_program.parameter(
			_name.get()))
{
	this->set(
		_initial_value);
}

template
<
	typename ValueType,
	fcppt::math::size_type N
>
void
sge::shader::parameter::vector<ValueType,N>::set(
	vector_type const &_vector)
{
	sge::cg::parameter::vector::set(
		parameter_.object(),
		_vector);
}

template
<
	typename ValueType,
	fcppt::math::size_type N
>
sge::shader::parameter::vector<ValueType,N>::~vector()
{
}

#endif
