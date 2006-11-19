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


#ifndef SGE_LOCK_PTR_HPP_INCLUDED
#define SGE_LOCK_PTR_HPP_INCLUDED

#include "./types.hpp"
#include "./texture_base.hpp"
#include "./volume_texture.hpp"

namespace sge
{

template<typename T> class lock_ptr {
public:
	lock_ptr(const T t, const lock_flag_t flags = LF_Default)
	 : t(t)
	{
		t->lock(flags);
	}

	lock_ptr(const T t, const cube_side side, const lock_flag_t flags = LF_Default)
	 : t(t)
	{
		t->lock(side);
	}

	lock_ptr(const T t, const lock_rect* const l)
	{
		t->lock(l);
	}

	lock_ptr(const T t, const lock_box* const l)
	{
		t->lock(l);
	}

	lock_ptr(const T t, const lock_flag_t flags, const std::size_t first, const std::size_t count)
	{
		t->lock(flags,first,count);
	}

	void unlock()
	{
		if(t)
		{
			t->unlock();
			_reset<T>::reset_ptr(t);
		}
	}

	~lock_ptr()
	{
		unlock();
	}
private:
	T t;

	template<typename U>
	struct _reset {
		static void reset_ptr(U& u)
		{
			u.reset();
		}
	};
	template<typename U>
	struct _reset<U*> {
		static void reset_ptr(U*& u)
		{
			u = 0;
		}
	};
};

}

#endif
