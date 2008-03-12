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


#ifndef SGE_SCOPED_LOCK_HPP_INCLUDED
#define SGE_SCOPED_LOCK_HPP_INCLUDED

#include <cstddef>
#include <boost/noncopyable.hpp>
#include "types.hpp"
#include "texture_base.hpp"
#include "volume_texture.hpp"
#include "cube_texture.hpp"

namespace sge
{

template<typename T>
class scoped_lock : boost::noncopyable {
public:
	struct wrapper {
		explicit wrapper(const T t)
		: t(t)
		{}

		T t;
	};

	explicit scoped_lock(const wrapper& w)
	 : w(w)
	{}

	void unlock()
	{
		if(w.t)
		{
			w.t->unlock();
			release();
		}
	}

	void release()
	{
		reset_<T>::reset_ptr(w.t);
	}

	~scoped_lock()
	{
		unlock();
	}
private:
	wrapper w;

	template<typename U>
	struct reset_ {
		static void reset_ptr(U& u)
		{
			u.reset();
		}
	};
	template<typename U>
	struct reset_<U*> {
		static void reset_ptr(U*& u)
		{
			u = 0;
		}
	};
};

template<typename T>
const typename scoped_lock<T>::wrapper
make_scoped_lock(
	const T t,
	const lock_flag_t flags)
{
	t->lock(flags);
	return scoped_lock<T>::wrapper(t);
}

template<typename T>
const typename scoped_lock<T>::wrapper
make_scoped_lock(
	const T t,
	const cube_side::type side,
	const lock_flag_t flags)
{
	t->lock(side, flags);
	return scoped_lock<T>::wrapper(t);
}

template<typename T, typename Sz>
const typename scoped_lock<T>::wrapper
make_scoped_lock(
	const T t,
	const Sz first,
	const Sz count,
	const lock_flag_t flags)
{
	t->lock(flags, first, count);
	return scoped_lock<T>::wrapper(t);
}

/*scoped_lock(const T t, const lock_rect& r)
	 : t(t)
	{
		t->lock(r);
	}

	scoped_lock(const T t, const lock_box& box)
	 : t(t)
	{
		t->lock(box);
	}*/

}

#endif
