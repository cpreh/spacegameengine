/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_BASIC_SCOPED_BUFFER_LOCK_IMPL_HPP_INCLUDED
#define SGE_RENDERER_BASIC_SCOPED_BUFFER_LOCK_IMPL_HPP_INCLUDED

#include <sge/renderer/basic_scoped_buffer_lock.hpp>

template<
	typename Ptr,
	typename View
>
sge::renderer::basic_scoped_buffer_lock<Ptr, View>::basic_scoped_buffer_lock(
	Ptr const _ptr,
	lock_mode::type const _flags,
	size_type const _first,
	size_type const _count
)
:
	ptr_(_ptr),
	view_(
		ptr_->lock(
			_flags,
			_first,
			_count
		)
	)
{}

template<
	typename Ptr,
	typename View
>
View const
sge::renderer::basic_scoped_buffer_lock<Ptr, View>::value() const
{
	return view_;
}

template<
	typename Ptr,
	typename View
>
sge::renderer::basic_scoped_buffer_lock<Ptr, View>::~basic_scoped_buffer_lock()
{
	ptr_->unlock();
}

#endif
