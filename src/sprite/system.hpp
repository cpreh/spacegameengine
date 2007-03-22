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
#include <boost/array.hpp>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include "../renderer/vertex_buffer.hpp"
#include "../renderer/index_buffer.hpp"
#include "../renderer/renderer.hpp"
#include "../renderer/renderable.hpp"
#include "../renderer/default_transformable.hpp"
#include "../raw_vector.hpp"
#include "../texture/texture_map.hpp"
#include "sprite_fwd.hpp"

namespace sge
{

class sprite_system : public default_transformable, public renderable, boost::noncopyable {
public:
	sprite_system(renderer_ptr rend, texture_map::handler_function handler, stage_type max_texture_level = 1);
	sprite_system(renderer_ptr rend, texture_map_ptr map, stage_type max_texture_level = 1);
	void render();
	void set_parameters();
	renderer_ptr get_renderer() const;
	stage_type max_tex_level() const;
	texture_map_ptr get_texture_map() const;
private:
	void init();
	sprite_list::iterator attach(sprite& s);
	void detach(const sprite& s);
	vertex_buffer::size_type free_vb_pos();

	friend class sprite;

	sprite_list sprites;

	texture_map_ptr tex_map;
	renderer_ptr rend;
	stage_type _max_tex;
	vertex_buffer_ptr vb;
	index_buffer_ptr ib;
	typedef std::vector<vertex_buffer::size_type> free_pos_vector;
	free_pos_vector free_pos;
	
	typedef raw_vector<vertex_buffer::value_type> vb_buf_type;
	vb_buf_type _sprite_vb_buf;
	typedef boost::array<index_buffer::value_type, detail::indices_per_sprite> ib_buf_type;
	ib_buf_type _sprite_ib_buf;
};

}

#endif

