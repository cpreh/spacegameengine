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


#ifndef SGE_OGL_VERTEX_FORMAT_HPP_INCLUDED
#define SGE_OGL_VERTEX_FORMAT_HPP_INCLUDED

#include <cstddef>
#include <boost/ptr_container/ptr_vector.hpp>
#include "../../shared_ptr.hpp"
#include "../../renderer/types.hpp"
#include "../../renderer/vertex_format.hpp"
#include "../../renderer/vertex_buffer.hpp"

namespace sge
{
namespace ogl
{

inline void* vbo_offset(const std::size_t sz)
{
	return reinterpret_cast<void*>(sz);
}

struct actor_info {
	actor_info(vertex_size _offset, vertex_size stride, vertex_size index);
	void*       offset;
	vertex_size stride;
	vertex_size index;
};

class actor_base {
public:
	actor_base(const actor_info& ai)
	 : ai(ai) {}
	virtual ~actor_base(){}
	virtual void operator()() const = 0;
protected:
	actor_info ai;
};

class vertex_format {
public:
	vertex_format(const sge::vertex_format& f);
	const offset_info& offsets() const { return oi; }
	void use_me() const;
private:
	offset_info oi;
	typedef boost::ptr_vector<actor_base> actor_array;
	actor_array actors;
};

}
}

#endif

