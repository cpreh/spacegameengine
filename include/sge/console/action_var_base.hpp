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


#ifndef SGE_CON_ACTION_VAR_BASE_HPP_INCLUED
#define SGE_CON_ACTION_VAR_BASE_HPP_INCLUED

#include "var_base.hpp"
#include "../string.hpp"
#include "../export.hpp"

namespace sge
{
namespace con
{

template<typename T,typename A>
struct SGE_CLASS_SYMBOL action_var_base : public var_base {
	typedef T value_type;
	typedef A action_type;

	void set(string const &s);
	
	string const get() const;

	T const &value() const;

	void value(T const &_t); 

	action_var_base(
		string const &name,
		A const &a,
		value_type const &_t = value_type());
private:
	action_type a;
	value_type t;
};

}
}

#endif
