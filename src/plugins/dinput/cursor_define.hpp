/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_DINPUT_CURSOR_DEFINE_HPP_INCLUDED
#define SGE_DINPUT_CURSOR_DEFINE_HPP_INCLUDED

#include "cursor_define_fwd.hpp"
#include "pixmap_cursor.hpp"
#include <awl/backends/windows/window/event/object_fwd.hpp>
#include <awl/backends/windows/window/event/processor_ptr.hpp>
#include <awl/backends/windows/window/event/return_type.hpp>
#include <awl/backends/windows/windows.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>

namespace sge
{
namespace dinput
{

class cursor_define
{
	FCPPT_NONCOPYABLE(
		cursor_define
	)
public:
	explicit cursor_define(
		awl::backends::windows::window::event::processor_ptr
	);

	~cursor_define();
private:
	awl::backends::windows::window::event::return_type
	on_cursor(
		awl::backends::windows::window::event::object const &
	);

	typedef fcppt::optional<
		HCURSOR
	> optional_hcursor;

	optional_hcursor previous_cursor_;

	dinput::pixmap_cursor const pixmap_cursor_;

	fcppt::signal::scoped_connection const connection_;
};

}
}

#endif
