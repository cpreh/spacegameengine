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


#include "../sprite_drawer.hpp"
#include "../sprite.hpp"
#include "../../algorithm.hpp"
#include "../../functional.hpp"

sge::sprite_drawer::sprite_drawer(const renderer_ptr rend)
 : rend(rend)
{}

void sge::sprite_drawer::draw(const sprite_list& sprites, const vertex_buffer_ptr vb, const index_buffer_ptr ib)
{
	unsigned first_index = 0;
	for(sprite_list::const_iterator it = sprites.begin(); it != sprites.end() && (*it)->visible(); )
	{
		unsigned num_objects;
		sprite_list::const_iterator next = first_mismatch_if(it, sprites.end(), num_objects, dereference_binder<const sprite*, const sprite*>(std::ptr_fun(sprite::equal_texture)));
		if((*it)->get_texture())
		{
			rend->set_texture(0,(*it)->get_texture());
			rend->render(vb,ib,0,vb->size(),PT_Triangle,num_objects*2,first_index);
		}
		first_index += num_objects * detail::indices_per_sprite;
		it = next;
	}
}

void sge::sprite_drawer::set_parameters()
{
	rend->set_bool_state(BS_EnableLighting,false);
	rend->projection_orthogonal();
	rend->set_filter_state(0,FARG_MinFilter,FARGV_Linear);
	rend->set_filter_state(0,FARG_MagFilter,FARGV_Linear);
}
