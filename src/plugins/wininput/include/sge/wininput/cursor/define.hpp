/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_WININPUT_CURSOR_DEFINE_HPP_INCLUDED
#define SGE_WININPUT_CURSOR_DEFINE_HPP_INCLUDED

#include <sge/wininput/cursor/define_fwd.hpp>
#include <sge/wininput/cursor/pixmap.hpp>
#include <awl/backends/windows/windows.hpp>
#include <awl/backends/windows/window/event/object_fwd.hpp>
#include <awl/backends/windows/window/event/processor_fwd.hpp>
#include <awl/backends/windows/window/event/return_type_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sge
{
namespace wininput
{
namespace cursor
{

class define
{
	FCPPT_NONCOPYABLE(
		define
	);
public:
	explicit
	define(
		awl::backends::windows::window::event::processor &
	);

	~define();
private:
	awl::backends::windows::window::event::return_type
	on_cursor(
		awl::backends::windows::window::event::object const &
	);

	typedef
	fcppt::optional<
		HCURSOR
	>
	optional_hcursor;

	optional_hcursor previous_cursor_;

	sge::wininput::cursor::pixmap const pixmap_;

	fcppt::signal::auto_connection const connection_;
};

}
}
}

#endif
