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


#ifndef SGE_RENDERER_SCOPED_LOCK_IMPL_HPP_INCLUDED
#define SGE_RENDERER_SCOPED_LOCK_IMPL_HPP_INCLUDED

#include "../scoped_lock.hpp"

template<typename T, typename Value>
sge::renderer::scoped_lock<T, Value>::scoped_lock(
	scoped_lock_wrapper<T, Value> const &w)
:
	w(w)
{}

template<typename T, typename Value>
void sge::renderer::scoped_lock<T, Value>::unlock()
{
	if(w.set())
	{
		w.unlock();
		release();
	}
}

template<typename T, typename Value>
void sge::renderer::scoped_lock<T, Value>::release()
{
	w.reset();
}

template<typename T, typename Value>
Value const
sge::renderer::scoped_lock<T, Value>::value() const
{
	return w.value();
}

template<typename T, typename Value>
sge::renderer::scoped_lock<T, Value>::~scoped_lock()
{
	unlock();
}

#endif
