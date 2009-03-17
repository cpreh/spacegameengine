/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/mainloop/skeleton.hpp>
#include <sge/mainloop/dispatch.hpp>
#include <sge/systems/instance.hpp>
#include <sge/input/system.hpp>
#include <boost/bind.hpp>

void sge::mainloop::skeleton::run()
{
	while(running)
	{
		dispatch();
		loop();
	}
}
	
sge::mainloop::skeleton::skeleton(
	systems::list const &s)
:
	running(true),
	sys(s)
{
	if (!sys.input_system())
		return;

	// this is to avoid hassle with shared_ptr(auto_ptr &)
	signal::auto_connection a = 
		sys.input_system()->register_callback(
			boost::bind(
				&skeleton::key_event,
				this,
				_1));
	
	input_con = signal::shared_connection(a);
}

void sge::mainloop::skeleton::exit()
{
	running = false;
}

sge::systems::instance const &
sge::mainloop::skeleton::system() const
{
	return sys;
}

sge::mainloop::skeleton::~skeleton()
{}

void sge::mainloop::skeleton::key_event(
	input::key_pair const &)
{}
