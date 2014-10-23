/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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

#include <sge/core/detail/class_symbol.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/console/error_callback.hpp>
#include <sge/console/error_function.hpp>
#include <sge/console/fallback.hpp>
#include <sge/console/fallback_signal.hpp>
#include <sge/console/function_map.hpp>
#include <sge/console/message_callback.hpp>
#include <sge/console/message_function.hpp>
#include <sge/console/prefix_fwd.hpp>
#include <sge/console/detail/symbol.hpp>
#include <sge/console/callback/parameters_fwd.hpp>
#include <sge/font/char_type.hpp>
#include <sge/font/string.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object_decl.hpp>
#include <fcppt/signal/scoped_connection.hpp>


namespace sge
{
namespace console
{

class SGE_CORE_DETAIL_CLASS_SYMBOL object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	SGE_CONSOLE_DETAIL_SYMBOL
	explicit
	object(
		sge::console::prefix
	);

	SGE_CONSOLE_DETAIL_SYMBOL
	~object();

	SGE_CONSOLE_DETAIL_SYMBOL
	fcppt::signal::auto_connection
	insert(
		sge::console::callback::parameters const &
	);

	SGE_CONSOLE_DETAIL_SYMBOL
	fcppt::signal::auto_connection
	register_fallback(
		sge::console::fallback const &
	);

	SGE_CONSOLE_DETAIL_SYMBOL
	fcppt::signal::auto_connection
	register_error_callback(
		sge::console::error_callback const &
	);

	SGE_CONSOLE_DETAIL_SYMBOL
	fcppt::signal::auto_connection
	register_message_callback(
		sge::console::message_callback const &
	);

	SGE_CONSOLE_DETAIL_SYMBOL
	void
	eval(
		sge::font::string const &
	);

	SGE_CONSOLE_DETAIL_SYMBOL
	void
	eval(
		sge::console::arg_list const &
	);

	SGE_CONSOLE_DETAIL_SYMBOL
	sge::console::function_map const &
	functions() const;

	SGE_CONSOLE_DETAIL_SYMBOL
	sge::font::char_type
	prefix() const;

	SGE_CONSOLE_DETAIL_SYMBOL
	void
	emit_error(
		sge::font::string const &
	);

	SGE_CONSOLE_DETAIL_SYMBOL
	void
	emit_message(
		sge::font::string const &
	);
private:
	fcppt::signal::object<
		sge::console::error_function
	> error_;

	fcppt::signal::object<
		sge::console::message_function
	> message_;

	sge::font::char_type const prefix_;

	sge::console::function_map funcs_;

	sge::console::fallback_signal fallback_;

	fcppt::signal::scoped_connection const
		help_connection_,
		man_connection_;

	void
	help_callback(
		sge::console::arg_list const &
	);

	void
	man_callback(
		sge::console::arg_list const &
	);

	void
	remove_function(
		sge::font::string const &
	);
};

}
}

#endif
