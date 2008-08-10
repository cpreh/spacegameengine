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


#ifndef SGE_RENDERER_VERTEX_BUFFER_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_BUFFER_HPP_INCLUDED

#include "vertex_format.hpp"
#include "vertex_view.hpp"
#include "vertex.hpp"
#include "lock_flags.hpp"
#include "resource_flags.hpp"
#include "../shared_ptr.hpp"
#include "../export.hpp"
#include <cstddef>

namespace sge
{
namespace renderer
{

class vertex_buffer {
public:
	typedef vertex::value_type      value_type;
	typedef vertex::size_type       size_type;
	typedef vertex::difference_type difference_type;
	
	typedef resource_flag_t         resource_flag_type;
	typedef lock_flag_t             lock_flag_type;

	static const size_type npos = static_cast<size_type>(-1);

	virtual vertex_view const lock(
		lock_flag_type flags,
		size_type offset = 0,
		size_type range = npos) = 0;

	virtual const_vertex_view const lock(
		size_type offset = 0,
		size_type range = npos) const = 0;

	virtual void unlock() const = 0;

	virtual size_type size() const = 0;
	virtual resource_flag_type flags() const = 0;

	virtual size_type stride() const = 0;

	virtual vertex_format const &get_vertex_format() const = 0;

	SGE_SYMBOL virtual ~vertex_buffer();
};

typedef shared_ptr<vertex_buffer> vertex_buffer_ptr;
typedef shared_ptr<vertex_buffer const> const_vertex_buffer_ptr;

}
}

#endif
