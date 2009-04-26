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



#ifndef SGE_MAINLOOP_SKELETON_HPP_INCLUDED
#define SGE_MAINLOOP_SKELETON_HPP_INCLUDED

#include <sge/systems/instance.hpp>
#include <sge/signal/shared_connection.hpp>
#include <sge/export.hpp>
#include <sge/noncopyable.hpp>
#include <sge/optional.hpp>

namespace sge
{
namespace systems
{
class list;
}
namespace input
{
class key_pair;
}

namespace mainloop
{

class SGE_CLASS_SYMBOL skeleton {
	SGE_NONCOPYABLE(skeleton)
public:
	SGE_SYMBOL void run();
protected:
	SGE_SYMBOL explicit skeleton(
		systems::list const &);	
	SGE_SYMBOL void exit();
	SGE_SYMBOL systems::instance const &system() const;
	SGE_SYMBOL virtual ~skeleton();
private:
	virtual void loop() = 0;
	virtual void key_event(
		input::key_pair const &);	

	bool running;
	systems::instance const sys;

	typedef optional<
		signal::shared_connection
	> optional_shared_connection;

	optional_shared_connection input_con;
};

}
}

#endif
