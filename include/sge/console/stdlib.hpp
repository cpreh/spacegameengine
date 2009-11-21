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


#ifndef SGE_CONSOLE_STDLIB_HPP_INCLUDED
#define SGE_CONSOLE_STDLIB_HPP_INCLUDED

#include <sge/console/object_fwd.hpp>
#include <sge/console/function_map.hpp>
#include <sge/signal/connection_manager.hpp>
#include <sge/export.hpp>
#include <sge/function/object.hpp>

namespace sge
{
namespace console
{
class stdlib
{
public:
	typedef sge::function::object<void (string const &)> print_callback;
	typedef sge::function::object<void (string const &)> error_callback;
	SGE_SYMBOL stdlib(
		object &,
		print_callback const &,
		error_callback const &);
private:
	object &object_;
	print_callback print_;
	error_callback error_;
	sge::signal::connection_manager connections;
	
	void fn_get(arg_list const &);
	void fn_set(arg_list const &);
	void fn_help(arg_list const &);
	void fn_lsvars(arg_list const &);
	void fn_man(arg_list const &);

	void print_function(function_map::const_reference);
};
}
}

#endif
