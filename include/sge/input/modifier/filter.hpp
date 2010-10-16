/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_INPUT_MODIFIER_FILTER_HPP_INCLUDED
#define SGE_INPUT_MODIFIER_FILTER_HPP_INCLUDED

#include <sge/input/modifier/states.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/input/keyboard/key_fwd.hpp>
#include <sge/input/processor_ptr.hpp>
#include <sge/symbol.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/container/map_decl.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace input
{
namespace modifier
{

class SGE_CLASS_SYMBOL filter
{
	FCPPT_NONCOPYABLE(filter)
public:
	typedef void
	fn_callback_type (
		keyboard::key_event const &,
		states const &
	);

	typedef fcppt::function::object<
		fn_callback_type
	> callback_type;

	typedef void
	fn_repeat_callback_type (
		keyboard::key const &,
		states const &
	);

	typedef fcppt::function::object<
		fn_repeat_callback_type
	> repeat_callback_type;

	SGE_SYMBOL explicit filter(
		processor_ptr
	);

	SGE_SYMBOL fcppt::signal::auto_connection
	register_callback(
		callback_type const &
	);

	SGE_SYMBOL fcppt::signal::auto_connection
	register_repeat_callback(
		repeat_callback_type const &
	);

	SGE_SYMBOL ~filter();
private:
	fcppt::signal::object<
		fn_callback_type
	> signal_;

	fcppt::signal::object<
		fn_repeat_callback_type
	> repeat_signal_;

	fcppt::signal::scoped_connection const
		ic_,
		irc_;

	modifier::states modifiers_;

	void
	input_callback(
		keyboard::key_event const &
	);

	void
	input_repeat_callback(
		keyboard::key const &
	);
};

}
}
}

#endif
