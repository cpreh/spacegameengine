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
#include "renderer.hpp"
#include "vertex_buffer.hpp"
#include "transformable.hpp"

namespace sge
{

class line_strip : public transformable, boost::noncopyable {
public:
	typedef vertex_buffer::size_type size_type;

	line_strip(renderer_ptr rend, color _col, size_type init_lines = 1);
	line_strip& add(const pos3& a);
	void set_color(color c);
	void draw(bool loop = false);
	pos3& operator[](size_type index);
	const pos3& operator[](size_type index) const;
	void clear();
private:
	typedef std::vector<pos3> pos_vector;
	const renderer_ptr rend;
	color _col;
	vertex_buffer_ptr vb;
	pos_vector vertices;
};

}

#endif
