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


#ifndef SGE_SPRITE_SYSTEM_HPP_INCLUDED
#define SGE_SPRITE_SYSTEM_HPP_INCLUDED

#include "../export.hpp"
#include "../renderer/vertex_buffer.hpp"
#include "../renderer/index_buffer.hpp"
#include "../renderer/device.hpp"
#include "../renderer/default_transformable.hpp"
#include "object.hpp"
#include <boost/noncopyable.hpp>

namespace sge
{
namespace sprite
{

class system : public renderer::default_transformable, boost::noncopyable {
public:
	SGE_SYMBOL explicit system(
		renderer::device_ptr rend);
	template<typename In>
		void render(In beg, In end);
	SGE_SYMBOL void render(object);
	SGE_SYMBOL const renderer::device_ptr get_renderer() const;
private:
	renderer::device_ptr        rend;
	renderer::vertex_buffer_ptr vb;
	renderer::index_buffer_ptr  ib;
};

}
}

#endif

