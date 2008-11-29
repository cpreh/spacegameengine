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


#ifndef SGE_MAINLOOP_SKELETON_HPP_INCLUDED
#define SGE_MAINLOOP_SKELETON_HPP_INCLUDED

#include "../export.hpp"
#include "../systems/instance.hpp"
#include "../signals/scoped_connection.hpp"
#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>

namespace sge
{
namespace systems
{
class list;
}
namespace input
{
struct key_pair;
}

namespace mainloop
{

class SGE_CLASS_SYMBOL skeleton : boost::noncopyable {
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

	typedef boost::optional<
		signals::scoped_connection
	> optional_scoped_connection;

	optional_scoped_connection const input_con;
};

}
}

#endif
