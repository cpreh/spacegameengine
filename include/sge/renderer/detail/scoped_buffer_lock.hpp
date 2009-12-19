/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_DETAIL_SCOPED_BUFFER_LOCK_HPP_INCLUDED
#define SGE_RENDERER_DETAIL_SCOPED_BUFFER_LOCK_HPP_INCLUDED

#include <sge/renderer/detail/npos.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/size_type.hpp>
#include <fcppt/noncopyable.hpp>
#include <sge/export.hpp>

namespace sge
{
namespace renderer
{
namespace detail
{

template<
	typename Ptr,
	typename View
>
class scoped_buffer_lock {
	FCPPT_NONCOPYABLE(scoped_buffer_lock)
public:
	SGE_SYMBOL scoped_buffer_lock(
		Ptr,
		lock_mode::type,
		size_type first = 0,
		size_type count = npos
	);

	SGE_SYMBOL View const
	value() const;

	SGE_SYMBOL ~scoped_buffer_lock();
private:
	Ptr const ptr;
	View const view;
};

}
}
}

#endif
