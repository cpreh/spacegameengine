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

#include <sge/renderer/index/view.hpp>
#include <sge/renderer/lock_flags.hpp>
#include <sge/renderer/resource_flags.hpp>
#include <sge/export.hpp>
#include <sge/noncopyable.hpp>

namespace sge
{
namespace renderer
{

class SGE_CLASS_SYMBOL index_buffer {
	SGE_NONCOPYABLE(index_buffer)
protected:
	SGE_SYMBOL index_buffer();
public:
	typedef resource_flag_t                resource_flag_type;
	typedef lock_flag_t                    lock_flag_type;

	typedef index::view                    view_type;
	typedef index::const_view              const_view_type;

	static size_type const npos = static_cast<size_type>(-1);

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

	virtual index::format::type index_format() const = 0;

	SGE_SYMBOL virtual ~index_buffer();
};

}
}

#endif
