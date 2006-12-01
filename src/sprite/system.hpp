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


#ifndef SGE_SPRITE_SYSTEM_HPP_INCLUDED
#define SGE_SPRITE_SYSTEM_HPP_INCLUDED

#include <list>
#include <string>
#include <vector>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include "../renderer/vertex_buffer.hpp"
#include "../renderer/index_buffer.hpp"
#include "../renderer/renderer.hpp"
#include "../math/matrix4x4.hpp"
#include "./sprite_fwd.hpp"
#include "../texture/texture_map.hpp"
#include "./sprite_drawer.hpp"

namespace sge
{

//template<typename TextureMap, typename Clipper, typename Transformator>
class sprite_system : public texture_map {
public:
//	typedef shared_ptr<TextureMap> texture_map_ptr;
	sprite_system(renderer_ptr rend, handler_function not_found_handler = 0/*, texture_map_ptr texture_map = texture_map_ptr()*/);
	void draw(vector2 translation = vector2());

//	texture_map_ptr get_texture_map() const;

	void enable_clipping(bool);
	void set_parameters();
	renderer_ptr get_renderer() const;
private:
	sprite_list::iterator attach(sprite& s);
	void detach(const sprite& s);
	vertex_buffer::size_type free_vb_pos();

	friend class sprite;

	sprite_list sprites;

	renderer_ptr rend;
	bool _clipping;
	sprite_drawer drawer;

	vertex_buffer_ptr vb;
	index_buffer_ptr ib;
	typedef std::vector<vertex_buffer::size_type> free_pos_vector;
	free_pos_vector free_pos;
};

}

#endif

