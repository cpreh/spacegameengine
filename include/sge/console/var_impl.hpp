/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_CONSOLE_VAR_IMPL_HPP_INCLUDED
#define SGE_CONSOLE_VAR_IMPL_HPP_INCLUDED

#include <sge/console/var.hpp>
#include <sge/exception.hpp>
#include <fcppt/text.hpp>
#include <sge/lexical_cast.hpp>

template<typename T>
void sge::console::var<T>::string(
	fcppt::string const &s)
{
	try
	{
		t = lexical_cast<value_type>(s);
	}
	catch (bad_lexical_cast const &)
	{
		throw exception(
			FCPPT_TEXT("couldn't parse variable \"")
			+ name()
			+ FCPPT_TEXT("\""));
	}
}

template<typename T>
fcppt::string const
sge::console::var<T>::string() const
{
	return lexical_cast<fcppt::string>(t);
}

template<typename T>
T const &sge::console::var<T>::value() const
{
	return t;
}

template<typename T>
void sge::console::var<T>::value(T const &_t)
{
	t = _t;
}

template<typename T>
sge::console::var<T>::var(
	object &object_,
	fcppt::string const &name,
	value_type const &t)
:
	var_base(
		object_,
		name),
	t(t)
{
	//late_construct();
}

#endif
