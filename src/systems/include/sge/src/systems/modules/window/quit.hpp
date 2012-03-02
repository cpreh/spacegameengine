/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_SYSTEMS_MODULES_WINDOW_QUIT_HPP_INCLUDED
#define SGE_SRC_SYSTEMS_MODULES_WINDOW_QUIT_HPP_INCLUDED

#include <sge/src/systems/modules/window/optional_dispatcher_ref.hpp>
#include <sge/src/systems/modules/window/quit_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/system_fwd.hpp>
#include <awl/system/event/quit_fwd.hpp>
#include <awl/window/event/destroy_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/signal/scoped_connection.hpp>


namespace sge
{
namespace systems
{
namespace modules
{
namespace window
{

class quit
{
	FCPPT_NONCOPYABLE(
		quit
	);
public:
	quit(
		sge::window::system &,
		sge::window::object &,
		sge::systems::modules::window::optional_dispatcher_ref const &
	);

	~quit();
private:
	void
	on_destroy(
		awl::window::event::destroy const &
	);

	void
	on_quit(
		awl::system::event::quit const &
	);

	sge::window::system &system_;

	sge::systems::modules::window::optional_dispatcher_ref const dispatcher_;

	fcppt::signal::scoped_connection const
		destroy_connection_,
		stop_dispatcher_connection_;
};

}
}
}
}

#endif
