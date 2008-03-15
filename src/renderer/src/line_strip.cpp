/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)
Copyright (C) 2008       Simon Stienen    (s.stienen@slashlife.org)

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


#include "../line_strip.hpp"
#include "../transform.hpp"
#include "../material.hpp"
#include "../../vector.hpp"
#include "../../math/matrix_impl.hpp"

sge::line_strip::line_strip(
	const renderer_ptr rend,
	const color col_,
	const size_type init_lines)
 : default_transformable(rend, math::matrix_identity(), math::matrix_orthogonal_xy()),
   rend(rend),
   col_(col_),
   vb(rend->create_vertex_buffer(vertex_format().add(vertex_usage::pos), init_lines + 1)),
   loop_(false)
{
	vertices.reserve(vb->size());
}

sge::line_strip& sge::line_strip::add(const pos3& a)
{
	vertices.push_back(a);
	return *this;
}

void sge::line_strip::set_color(const color c)
{
	col_ = c;
}

void sge::line_strip::render()
{
	if(vertices.size() <= 1)
		return;
	rend->set_state((
		bool_state::enable_alpha_blending = false,
		bool_state::enable_lighting = true,
		color_state::ambient_light_color = col_
	));
	set_matrices();
//	rend->set_material(material(color4(1,1,1,1), color4(1,1,1,1)));
	rend->set_texture(texture_ptr());

	if(vb->size() < vertices.size())
		vb->resize(vertices.size());
	vb->set_data(reinterpret_cast<vertex_buffer::const_pointer>(sge::data(vertices)), 0, vertices.size());
	rend->render(
		vb,
		0,
		static_cast<index_buffer::size_type>(vertices.size()),
		loop_
			? nonindexed_primitive_type::line_loop
			: nonindexed_primitive_type::line_strip);
}

sge::pos3& sge::line_strip::operator[](const size_type index)
{
	return vertices[index];
}

const sge::pos3& sge::line_strip::operator[](const size_type index) const
{
	return vertices[index];
}

void sge::line_strip::clear()
{
	vertices.clear();
}

void sge::line_strip::loop(const bool b)
{
	loop_ = b;
}
