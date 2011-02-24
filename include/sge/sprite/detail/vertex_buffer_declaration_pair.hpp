/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_DETAIL_VERTEX_BUFFER_DECLARATION_PAIR_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_VERTEX_BUFFER_DECLARATION_PAIR_HPP_INCLUDED

#include <sge/renderer/vertex_buffer_ptr.hpp>
#include <sge/renderer/vertex_declaration_ptr.hpp>
#include <utility>

namespace sge
{
namespace sprite
{
namespace detail
{

typedef std::pair<
	sge::renderer::vertex_declaration_ptr,
	sge::renderer::vertex_buffer_ptr
> vertex_buffer_declaration_pair;

}
}
}

#endif
