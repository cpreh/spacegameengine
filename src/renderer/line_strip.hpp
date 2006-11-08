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

template<typename PointType>
class line_strip : coordinate_transformator<PointType>, boost::noncopyable {
public:
	typedef vertex_buffer::size_type size_type;

	line_strip(const renderer_ptr rend, const color _col, const size_type init_lines = 50)
	 : rend(rend), _col(_col), vb(rend->create_vertex_buffer(vertex_format().add(VU_Pos), init_lines + 1)), pos(0)
	{}

	line_strip& add(const PointType a)
	{
		if(pos >= vb->size())
		{
			vertex_buffer_ptr tmp = rend->create_vertex_buffer(vb->get_vertex_format(), vb->size()*2);
			{
				lock_ptr<vertex_buffer_ptr> _l1(tmp), _l2(vb);
				copy(vb->data(),vb->data()+vb->size()*vb->stride(),tmp->data());
			}
			vb = tmp;
		}

		const pos3 p = transform(a);
		vb->set_data(reinterpret_cast<vertex_buffer::const_pointer>(&p),pos,1);
		++pos;
		return *this;
	}

	void set_color(const color c)
	{
		_col = c;
	}

	void draw()
	{
		if(pos <= 1)
			return;
		rend->set_bool_state(BS_EnableAlphaBlending,false);
		rend->set_transformation(matrix4x4<space_unit>());
		rend->set_bool_state(BS_EnableLighting,true);
		rend->set_material(material(color4(1,1,1,1),color4(1,1,1,1)));
		rend->set_int_state(IS_AmbientLightColor, _col);
		rend->set_filter_state(0,FARG_MinFilter,FARGV_Point);
		rend->set_filter_state(0,FARG_MagFilter,FARGV_Point);
		rend->set_texture(0,texture_ptr());
		rend->render(vb,index_buffer_ptr(),0,pos,PT_LineStrip,pos-1);
	}

	void clear()
	{
		pos = 0;
	}
private:
	const renderer_ptr rend;
	color _col;
	vertex_buffer_ptr vb;
	size_type pos;
};

}

#endif
