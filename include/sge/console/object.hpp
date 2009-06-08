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


#ifndef SGE_CONSOLE_OBJECT_HPP_INCLUDED
#define SGE_CONSOLE_OBJECT_HPP_INCLUDED

#include <sge/console/callbacks.hpp>
#include <sge/console/variable_map.hpp>
#include <sge/console/function_map.hpp>
#include <sge/console/var_base_fwd.hpp>
#include <sge/signal/auto_connection.hpp>
#include <sge/export.hpp>
#include <sge/noncopyable.hpp>

namespace sge
{
namespace console
{
class SGE_CLASS_SYMBOL object
{
	SGE_NONCOPYABLE(object)
	public:
	SGE_SYMBOL explicit object(string::value_type prefix);
	
	SGE_SYMBOL sge::signal::auto_connection insert(
		string const &name,
		callback const &,
		string const &description = string());

	SGE_SYMBOL sge::signal::auto_connection register_fallback(
		fallback const &
	);
	
	SGE_SYMBOL void eval(string const &);
	SGE_SYMBOL variable_map const &variables() const;
	SGE_SYMBOL variable_map &variables();
	SGE_SYMBOL function_map const &functions() const;
	private:
	friend class var_base;
	
	variable_map vars_;
	function_map funcs_;
	fallback_signal fallback_;
	string::value_type prefix_;

	void insert(var_base &);
	void erase(var_base &);
};
}
}

#endif
