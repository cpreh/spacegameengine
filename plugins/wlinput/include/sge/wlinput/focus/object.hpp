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


#ifndef SGE_WLINPUT_FOCUS_OBJECT_HPP_INCLUDED
#define SGE_WLINPUT_FOCUS_OBJECT_HPP_INCLUDED

#include <sge/input/focus/object.hpp>
#include <sge/input/focus/shared_ptr.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/wlinput/xkb_context_fwd.hpp>
#include <sge/wlinput/focus/data.hpp>
#include <sge/wlinput/focus/holder.hpp>
#include <sge/wlinput/focus/object_fwd.hpp>
#include <awl/backends/wayland/seat_fwd.hpp>
#include <awl/backends/wayland/window/object_fwd.hpp>
#include <awl/event/container.hpp>
#include <awl/event/container_reference.hpp>
#include <fcppt/enable_shared_from_this_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sge
{
namespace wlinput
{
namespace focus
{

class object
:
	public
		sge::input::focus::object,
	public
		fcppt::enable_shared_from_this<
			sge::wlinput::focus::object
		>
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		fcppt::log::object &,
		sge::window::object &,
		sge::wlinput::xkb_context const &,
		awl::backends::wayland::window::object const &,
		awl::event::container_reference,
		awl::backends::wayland::seat const &
	);

	~object()
	override;

	sge::window::object &
	window() const
	override;

	sge::input::focus::shared_ptr
	get_shared_ptr();
private:
	awl::event::container
	on_key_repeat();

	sge::wlinput::focus::holder const impl_;

	sge::wlinput::focus::data data_;

	fcppt::signal::auto_connection const event_connection_;
};

}
}
}

#endif
