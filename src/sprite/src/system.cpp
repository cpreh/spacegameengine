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


#include "../system.hpp"
#include "../sprite.hpp"
#include "../../renderer/vertex_format.hpp"
#include "../../renderer/transform.hpp"

const unsigned init_sprites = 25;

sge::sprite_system::sprite_system(const renderer_ptr rend, const stage_type _max_tex)
 : default_transformable(rend, matrix_2d_to_3d(), math::matrix_orthogonal_xy()),
   rend(rend),
   _max_tex(_max_tex),
   vb(rend->create_vertex_buffer(vertex_format().add(vertex_usage::pos).add(vertex_usage::diffuse).add(vertex_usage::tex, _max_tex), init_sprites * detail::vertices_per_sprite, resource_flags::write_only | resource_flags::dynamic)),
   ib(rend->create_index_buffer(init_sprites * detail::indices_per_sprite))
{}

void sge::sprite_system::set_parameters()
{
	set_matrices();
	rend->set_bool_state(bool_state::enable_lighting, false);
	rend->set_bool_state(bool_state::enable_alpha_blending, true);
	rend->set_bool_state(bool_state::enable_culling, false);
}

const sge::renderer_ptr sge::sprite_system::get_renderer() const
{
	return rend;
}

sge::stage_type sge::sprite_system::max_tex_level() const
{
	return _max_tex;
}
