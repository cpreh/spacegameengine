/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_WININPUT_FOCUS_OBJECT_HPP_INCLUDED
#define SGE_WININPUT_FOCUS_OBJECT_HPP_INCLUDED

#include <sge/input/focus/object.hpp>
#include <sge/input/key/pressed.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/wininput/focus/object_fwd.hpp>
#include <awl/backends/windows/window/event/generic_fwd.hpp>
#include <awl/event/base_unique_ptr.hpp>
#include <awl/event/container.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <awl/window/event/base_fwd.hpp>
#include <fcppt/enable_shared_from_this_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sge
{
namespace wininput
{
namespace focus
{

class object
:
	public
		sge::input::focus::object,
	public
		fcppt::enable_shared_from_this<
			sge::wininput::focus::object
		>
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	explicit
	object(
		sge::window::object &
	);

	~object()
	override;

	sge::window::object &
	window() const
	override;
private:
	awl::event::container
	on_event(
		awl::window::event::base const &
	);

	awl::event::optional_base_unique_ptr
	on_window_event(
		awl::backends::windows::window::event::generic const &
	);

	awl::event::base_unique_ptr
	on_key(
		awl::backends::windows::window::event::generic const &,
		sge::input::key::pressed
	);

	sge::window::object &window_;

	fcppt::signal::auto_connection const event_connection_;
};

}
}
}

#endif
