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


#ifndef SGE_LINE_STRIP_HPP_INCLUDED
#define SGE_LINE_STRIP_HPP_INCLUDED

#include <boost/noncopyable.hpp>
#include <vector>
#include "../algorithm.hpp"
#include "./renderer.hpp"
#include "./vertex_buffer.hpp"
#include "./transform.hpp"

namespace sge
{

template<typename PointType> struct coordinate_transformator;

template<> struct coordinate_transformator<pos3> {
	pos3 transform(const pos3 p) const { return p; }
};

template<> struct coordinate_transformator<point> {
	pos3 transform(const point p) const { return space_2d_to_3d(p); }
};

template<typename PointType, template<typename> class Transformator = coordinate_transformator>
class line_strip : public Transformator<PointType>, boost::noncopyable {
public:
	typedef vertex_buffer::size_type size_type;

	line_strip(const renderer_ptr rend, const color _col, const size_type init_lines = 50)
	 : rend(rend), _col(_col), vb(rend->create_vertex_buffer(vertex_format().add(VU_Pos),init_lines+1))
	{
		vertices.reserve(init_lines+1);
	}

	line_strip& add(const PointType a)
	{
		const pos3 p = transform(a);
		vertices.push_back(p);
		return *this;
	}

	void set_color(const color c)
	{
		_col = c;
	}

	void draw(const bool loop = false)
	{
		if(vertices.size() <= 1)
			return;
		rend->set_bool_state(BS_EnableAlphaBlending,false);
		rend->transform(math::matrix_identity());
		rend->set_bool_state(BS_EnableLighting,true);
		rend->set_material(material(color4(1,1,1,1),color4(1,1,1,1)));
		rend->set_int_state(IS_AmbientLightColor, _col);
		rend->set_filter_state(0,FARG_MinFilter,FARGV_Point);
		rend->set_filter_state(0,FARG_MagFilter,FARGV_Point);
		rend->set_texture(0,texture_ptr());

		if(vb->size() < vertices.size())
			vb->resize(vertices.size());
		vb->set_data(reinterpret_cast<vertex_buffer::const_pointer>(&vertices[0]),0,vertices.size());
		rend->render(vb, index_buffer_ptr(), 0, vertices.size(), loop ? PT_LineLoop : PT_LineStrip, vertices.size()-1);
	}

	pos3& operator[](const size_type index)
	{
		return vertices[index];
	}

	const pos3& operator[](const size_type index) const
	{
		return vertices[index];
	}

	void clear()
	{
		vertices.clear();
	}
private:
	typedef std::vector<pos3> pos_vector;
	const renderer_ptr rend;
	color _col;
	pos_vector vertices;
	vertex_buffer_ptr vb;
};

}

#endif
