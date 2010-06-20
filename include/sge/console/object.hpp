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

#include <sge/console/callback.hpp>
#include <sge/console/fallback.hpp>
#include <sge/console/fallback_signal.hpp>
#include <sge/console/variable_map.hpp>
#include <sge/console/function_map.hpp>
#include <sge/console/var_base_fwd.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/symbol.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/string.hpp>
#include <fcppt/char_type.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace console
{

class SGE_CLASS_SYMBOL object
{
	FCPPT_NONCOPYABLE(object)
public:
	SGE_SYMBOL explicit object(
		fcppt::char_type prefix
	);

	SGE_SYMBOL fcppt::signal::auto_connection
	insert(
		fcppt::string const &name,
		callback const &,
		fcppt::string const &description = fcppt::string()
	);

	SGE_SYMBOL fcppt::signal::auto_connection
	register_fallback(
		fallback const &
	);

	SGE_SYMBOL void
	eval(
		fcppt::string const &
	);

	SGE_SYMBOL void
	eval(
		console::arg_list const &
	);

	SGE_SYMBOL variable_map const &
	variables() const;

	SGE_SYMBOL variable_map &
	variables();

	SGE_SYMBOL function_map const &
	functions() const;

	SGE_SYMBOL fcppt::char_type
	prefix() const;
private:
	friend class var_base;

	fcppt::char_type const prefix_;

	variable_map vars_;

	function_map funcs_;

	fallback_signal fallback_;

	void
	insert(
		var_base &
	);

	void
	erase(
		var_base &
	);
};

}
}

#endif
