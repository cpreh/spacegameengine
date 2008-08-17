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


#ifndef SGE_RENDERER_LINE_STRIP_HPP_INCLUDED
#define SGE_RENDERER_LINE_STRIP_HPP_INCLUDED

#include "renderer.hpp"
#include "vertex_buffer.hpp"
#include "default_transformable.hpp"
#include "../export.hpp"
#include <boost/noncopyable.hpp>
#include <vector>

namespace sge
{
namespace renderer
{

class SGE_CLASS_SYMBOL line_strip : public default_transformable, boost::noncopyable {
public:
	typedef vertex_buffer::size_type size_type;

	SGE_SYMBOL line_strip(device_ptr rend, color col, size_type init_lines = 1);
	SGE_SYMBOL line_strip& add(const pos3& a);
	SGE_SYMBOL void set_color(color c);
	SGE_SYMBOL void render();
	SGE_SYMBOL pos3& operator[](size_type index);
	SGE_SYMBOL const pos3& operator[](size_type index) const;
	SGE_SYMBOL void clear();
	SGE_SYMBOL void loop(bool);
private:
	typedef std::vector<pos3> pos_vector;
	const device_ptr rend;
	color col_;
	vertex_buffer_ptr vb;
	bool loop_;
	pos_vector vertices;
};

}
}

#endif
