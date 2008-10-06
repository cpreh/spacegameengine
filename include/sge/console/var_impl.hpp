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


#ifndef SGE_CON_VAR_IMPL_HPP_INCLUDED
#define SGE_CON_VAR_IMPL_HPP_INCLUDED

#include "var.hpp"
#include "exception.hpp"
#include "../text.hpp"
#include <boost/lexical_cast.hpp>

template<typename T>
void sge::con::var<T>::set(string const &s) 
{ 
	try
	{
		t = boost::lexical_cast<T>(s); 
	} 
	catch (boost::bad_lexical_cast const &)
	{
		throw exception(
			SGE_TEXT("couldn't parse variable \"")
			+ name()
			+ SGE_TEXT("\""));
	}
}

template<typename T>
sge::string const
sge::con::var<T>::get() const
{
	return boost::lexical_cast<string>(t);
}

template<typename T>
T const &sge::con::var<T>::value() const
{
	return t;
}

template<typename T>
void sge::con::var<T>::value(T const &_t)
{
	t = _t;
}

template<typename T>
sge::con::var<T>::var(
	string const &name,
	value_type const &t) 
:
	var_base(name),
	t(t)
{
	late_construct();
}

#endif
