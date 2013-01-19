/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_EVDEV_FOCUS_MANAGER_HPP_INCLUDED
#define SGE_EVDEV_FOCUS_MANAGER_HPP_INCLUDED

#include <sge/evdev/focus_manager_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/window/event/focus_in_fwd.hpp>
#include <awl/window/event/focus_out_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/scoped_connection.hpp>


namespace sge
{
namespace evdev
{

class focus_manager
{
	FCPPT_NONCOPYABLE(
		focus_manager
	);
public:
	focus_manager(
		awl::system::object &,
		sge::window::object const &
	);

	~focus_manager();

	bool
	focus() const;
private:
	void
	on_focus_in(
		awl::window::event::focus_in const &
	);

	void
	on_focus_out(
		awl::window::event::focus_out const &
	);

	bool focus_;

	fcppt::signal::scoped_connection const
		focus_in_connection_,
		focus_out_connection_;
};

}
}

#endif
