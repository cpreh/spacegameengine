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


#include "../line_strip.hpp"
#include "../transform.hpp"
#include "../../vector.hpp"

sge::line_strip::line_strip(const renderer_ptr rend, const color _col, const size_type init_lines)
 : default_transformable(rend, matrix_2d_to_3d(), math::matrix_orthogonal_xy()),
   rend(rend),
   _col(_col),
   vb(rend->create_vertex_buffer(vertex_format().add(VU_Pos),init_lines+1)),
   _loop(false)
{
	vertices.reserve(init_lines+1);
}

sge::line_strip& sge::line_strip::add(const pos3& a)
{
	vertices.push_back(a);
	return *this;
}

void sge::line_strip::set_color(const color c)
{
	_col = c;
}

void sge::line_strip::render()
{
	if(vertices.size() <= 1)
		return;
	rend->set_bool_state(BS_EnableAlphaBlending,false);
	set_matrices();
	rend->set_bool_state(BS_EnableLighting,true);
	rend->set_material(material(color4(1,1,1,1),color4(1,1,1,1)));
	rend->set_int_state(IS_AmbientLightColor, _col);
	rend->set_texture(texture_ptr());

	if(vb->size() < vertices.size())
		vb->resize(vertices.size());
	vb->set_data(reinterpret_cast<vertex_buffer::const_pointer>(sge::data(vertices)),0,vertices.size());
	rend->render(vb, index_buffer_ptr(), 0, vertices.size(), _loop ? PT_LineLoop : PT_LineStrip, vertices.size()-1);
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

void sge::line_strip::set_parameters()
{
}

void sge::line_strip::loop(const bool b)
{
	_loop = b;
}
