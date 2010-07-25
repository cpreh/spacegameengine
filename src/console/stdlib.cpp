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


#include <sge/console/stdlib.hpp>
#include <sge/console/object.hpp>
#include <sge/console/exception.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/signal/shared_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>
#include <fcppt/lexical_cast.hpp>
#include <boost/foreach.hpp>

sge::console::stdlib::stdlib(
	object &_object)
:
	object_(_object),
	connections(
		fcppt::assign::make_container<
			fcppt::signal::connection_manager::container
		>
		(
			fcppt::signal::shared_connection(
				object_.insert(
					FCPPT_TEXT("help"),
					std::tr1::bind(
						&stdlib::fn_help,
						this,
						std::tr1::placeholders::_1),
					FCPPT_TEXT("list available functions"))))
		(
			fcppt::signal::shared_connection(
				object_.insert(
					FCPPT_TEXT("lsfuncs"),
					std::tr1::bind(
						&stdlib::fn_help,
						this,
						std::tr1::placeholders::_1),
					FCPPT_TEXT("list available functions"))))
		(
			fcppt::signal::shared_connection(
				object_.insert(
					FCPPT_TEXT("man"),
					std::tr1::bind(
						&stdlib::fn_man,
						this,
						std::tr1::placeholders::_1),
					FCPPT_TEXT("usage: man <function> - display help to <function>")))))
{
}

void 
sge::console::stdlib::fn_help(
	arg_list const &)
{
	function_map const &fns = 
		object_.functions();

	object_.emit_message(
		fcppt::lexical_cast<
			fcppt::string
		>(
			fns.size()
		)
		+ FCPPT_TEXT(" available functions:")
	);

	BOOST_FOREACH(function_map::const_reference p,fns)
		print_function(
			p);
}

void 
sge::console::stdlib::fn_man(
	arg_list const &v)
{
	if (v.size() < 2 || v[1].empty())
		object_.emit_error(
			FCPPT_TEXT("no function given"));

	function_map const &fns = 
		object_.functions();

	function_map::const_iterator i = 
		fns.find(
			v[1]);

	if (i == fns.end())
	{
		object_.emit_error(
			FCPPT_TEXT("function \"")+v[1]+FCPPT_TEXT("\" not found"));
		return;
	}

	print_function(
		*i);
}

void 
sge::console::stdlib::print_function(
	function_map::const_reference p)
{
	if (p.second->description().empty())
		object_.emit_message(
			p.first);
	else
		object_.emit_message(
			p.first+FCPPT_TEXT(": ")+p.second->description());
}
