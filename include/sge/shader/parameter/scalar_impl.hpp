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


#ifndef SGE_SHADER_PARAMETER_SCALAR_IMPL_HPP_INCLUDED
#define SGE_SHADER_PARAMETER_SCALAR_IMPL_HPP_INCLUDED

#include <sge/cg/parameter/scalar/set.hpp>
#include <sge/cg/program/object.hpp>
#include <sge/shader/parameter/name.hpp>
#include <sge/shader/parameter/scalar_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <fcppt/config/external_end.hpp>
#include <iostream>

template<typename ValueType>
sge::shader::parameter::scalar<ValueType>::scalar(
	sge::cg::program::object &_program,
	sge::shader::parameter::name const &_name,
	value_type const _initial_value)
:
	parameter_(
		_program.parameter(
			_name.get()))
{
	this->set(
		_initial_value);
}

template<typename ValueType>
void
sge::shader::parameter::scalar<ValueType>::set(
	value_type const _scalar)
{
	typedef typename
	boost::mpl::if_
	<
		boost::is_same<value_type,bool>,
		int,
		typename
		boost::mpl::if_
		<
			boost::is_integral<value_type>,
			int,
			value_type
		>::type
	>::type
	promoted_type;

	sge::cg::parameter::scalar::set(
		parameter_.object(),
		static_cast<promoted_type>(
			_scalar));
}

template<typename ValueType>
sge::shader::parameter::scalar<ValueType>::~scalar()
{
}

#endif
