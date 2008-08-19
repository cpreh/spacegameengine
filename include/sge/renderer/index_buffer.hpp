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


#ifndef SGE_RENDERER_INDEX_BUFFER_HPP_INCLUDED
#define SGE_RENDERER_INDEX_BUFFER_HPP_INCLUDED

#include "lock_flags.hpp"
#include "resource_flags.hpp"
#include "index_view.hpp"
#include "../shared_ptr.hpp"
#include "../export.hpp"
#include <cstddef>

namespace sge
{
namespace renderer
{

class index_buffer {
public:
	typedef std::size_t                           size_type;
	typedef std::ptrdiff_t                        difference_type;
	typedef resource_flag_t                       resource_flag_type;
	typedef lock_flag_t                           lock_flag_type;

	typedef dynamic_index_view                    view_type;
	typedef const_dynamic_index_view              const_view_type;

	static const size_type npos = static_cast<size_type>(-1);

	virtual view_type const lock(
		lock_flag_type flags,
		size_type offset = 0,
		size_type range = npos) = 0;

	virtual const_view_type const lock(
		size_type offset = 0,
		size_type range = npos) const = 0;

	virtual void unlock() const = 0;

	virtual size_type size() const = 0;
	virtual resource_flag_t flags() const = 0;

	virtual index_format::type get_index_format() const = 0;

	SGE_SYMBOL virtual ~index_buffer();
};

typedef shared_ptr<index_buffer> index_buffer_ptr;
typedef shared_ptr<index_buffer const> const_index_buffer_ptr;

}
}

#endif
