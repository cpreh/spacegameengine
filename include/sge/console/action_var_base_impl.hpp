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


#ifndef SGE_CON_ACTION_VAR_BASE_IMPL_HPP_INCLUED
#define SGE_CON_ACTION_VAR_BASE_IMPL_HPP_INCLUED

#include "action_var_base.hpp"
#include "exception.hpp"
#include "../text.hpp"
#include <boost/lexical_cast.hpp>

template<typename T, typename A>
void sge::con::action_var_base<T, A>::set(
	string const &s) 
{ 
	try
	{
		value(boost::lexical_cast<T>(s));
	} 
	catch (boost::bad_lexical_cast const &)
	{
		throw exception(
			SGE_TEXT("couldn't parse variable \"")
			+name()
			+SGE_TEXT("\""));
	}
}

template<typename T, typename A>
sge::string const
sge::con::action_var_base<T, A>::get() const
{
	return boost::lexical_cast<string>(t);
}

template<typename T, typename A>
const T &sge::con::action_var_base<T, A>::value() const
{
	return t;
}

template<typename T, typename A>
void sge::con::action_var_base<T, A>::value(
	T const &_t) 
{ 
	t = _t;
	t = a(_t,t); 
}

template<typename T, typename A>
sge::con::action_var_base<T, A>::action_var_base(
	string const &name,
	A const &a_,
	value_type const &t_) 
:
	var_base(name),
	a(a_),
	t(a(t_,t_))
{
	late_construct();
}

#endif
