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


#ifndef SGE_SPRITE_INTRUSIVE_SYSTEM_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_SYSTEM_HPP_INCLUDED

#include "intrusive_object.hpp"
#include "../renderer/device.hpp"
#include "../renderer/vertex_buffer.hpp"
#include "../renderer/index_buffer.hpp"
#include "../renderer/default_transformable.hpp"
#include <boost/intrusive/list.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/noncopyable.hpp>

namespace sge
{
namespace sprite
{

class intrusive_system : public renderer::default_transformable, boost::noncopyable {
public:
	SGE_SYMBOL explicit intrusive_system(
		renderer::device_ptr);
	
	SGE_SYMBOL void render();

	SGE_SYMBOL renderer::device_ptr const
	get_renderer() const;
private:
	typedef boost::intrusive::list<
		intrusive_object,
		boost::intrusive::constant_time_size<false>
	> sprite_list;

	void render(
		sprite_list const &);
	void add(
		intrusive_object &,
		intrusive_object::order_type);
	friend class intrusive_object;

	renderer::device_ptr const rend;
	renderer::vertex_buffer_ptr vb;
	renderer::index_buffer_ptr ib;
	typedef boost::ptr_map<
		intrusive_object::order_type,
		sprite_list
	> sprite_level_map;

	sprite_level_map sprite_levels;
};

}
}

#endif
