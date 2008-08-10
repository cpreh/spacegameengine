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

	static const size_type npos = static_cast<size_type>(-1);

	virtual void lock(
		lock_flag_t flags,
		size_type offset = 0,
		size_type range = npos) = 0;
	virtual void unlock() = 0;
	virtual void data(
		const_dynamic_index_view const &) = 0;
	void sub_data(
		const_dynamic_index_view const &,
		size_type offset);

	virtual dynamic_index_view const view() = 0;
	virtual const_dynamic_index_view const view() const = 0;

	virtual size_type size() const = 0;
	virtual resource_flag_t flags() const = 0;

	virtual void resize(
		size_type) = 0;

	SGE_SYMBOL virtual ~index_buffer();
private:
	virtual void do_sub_data(
		const_dynamic_index_view const &,
		size_type offset) = 0;
};

typedef shared_ptr<index_buffer> index_buffer_ptr;

}
}

#endif
