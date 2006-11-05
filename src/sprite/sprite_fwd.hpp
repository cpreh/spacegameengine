/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_SPRITE_FWD_HPP_INCLUDED
#define SGE_SPRITE_FWD_HPP_INCLUDED

#include <list>
#include "../renderer/vertex_buffer.hpp"
#include "../renderer/index_buffer.hpp"

namespace sge
{

class sprite_system;
class sprite;
typedef std::list<sprite*> sprite_list;

namespace detail
{
	const index_buffer::size_type indices_per_sprite = 6;
	const vertex_buffer::size_type vertices_per_sprite = 4;
}

}

#endif
