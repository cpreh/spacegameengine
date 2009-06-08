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


#ifndef SGE_SPRITE_INTRUSIVE_SYSTEM_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_SYSTEM_HPP_INCLUDED

#include <sge/sprite/intrusive/system_fwd.hpp>
#include <sge/sprite/intrusive/object.hpp> // TODO: can we get rid of this?
#include <sge/sprite/intrusive/order.hpp>
#include <sge/sprite/system_base.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <boost/intrusive/list.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/noncopyable.hpp>

namespace sge
{
namespace sprite
{
namespace intrusive
{

class system : public system_base {
public:
	SGE_SYMBOL explicit system(
		renderer::device_ptr);
	
	SGE_SYMBOL ~system();
	
	SGE_SYMBOL void render();
private:
	typedef boost::intrusive::list<
		object,
		boost::intrusive::constant_time_size<
			false
		>
	> sprite_list;

	void render(
		sprite_list const &);
	void add(
		object &,
		order);
	friend class object;

	typedef boost::ptr_map<
		order,
		sprite_list
	> sprite_level_map;

	sprite_level_map sprite_levels;
};

}
}
}

#endif
