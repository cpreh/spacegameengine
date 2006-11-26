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


#ifndef SGE_SHARED_PTR_HPP_INCLUDED
#define SGE_SHARED_PTR_HPP_INCLUDED

#include <ostream>
#include <cstddef>
#include "./smart_ptr_policies.hpp"
#include "./ptr_cast.hpp"

namespace sge
{

namespace detail {
struct static_cast_tag{};
struct dynamic_cast_tag{};
}
	
template<typename T, template <typename> class Deleter = heap_deleter> class shared_ptr : Deleter<T> {
	typedef std::size_t counter_type;
public:
	typedef T     value_type;
	typedef T&    reference;
	typedef T*    pointer;
	
	shared_ptr()
	 : ptr(0), counter(new counter_type(1)) {}

	explicit shared_ptr(const pointer p)
	 : ptr(p), counter(new counter_type(1)) {}

	shared_ptr(const shared_ptr& r) { _assign(r); }
	template<typename Other> shared_ptr(const shared_ptr<Other,Deleter>& r) { _assign(r); }
	template<typename Other> shared_ptr(const shared_ptr<Other,Deleter>& r, detail::dynamic_cast_tag)
	{
		counter = r.counter;
		++(*counter);
		ptr = ptr_cast<pointer>(r.get());
	}
	template<typename Other> shared_ptr(const shared_ptr<Other,Deleter>& r, detail::static_cast_tag)
	{
		counter = r.counter;
		++(*counter);
		ptr = static_cast<pointer>(r.get());
	}

		
	shared_ptr& operator=(const shared_ptr& r)
	{
		if(r != *this)
		{
			_release();
			_assign(r);
		}
		return *this;
	}
		
	pointer get() const { return ptr; }
	pointer operator->() const { return ptr; }
	reference operator*() const { return *ptr; }

	~shared_ptr() { _release(); }

	void reset(const pointer p = 0)
	{
		if(p != get())
		{
			_release();
			ptr = p;
			counter = new counter_type(1);
		}
	}
private:
	struct _dummy {
		void operator delete(void*);
	};
public:
	operator _dummy*() const
	{
		if(!(*this)) return 0;
		static _dummy d;
		return &d;
	}
private:
	template<typename Other, template<typename> class OtherDeleter> friend class shared_ptr;

	void _release()
	{
		if(--(*counter) == 0)
		{
			delete_(ptr);
			ptr = 0;
			delete counter;
			counter = 0;
		}
	}

	void _assign(const shared_ptr& r)
	{
		counter = r.counter;
		ptr = r.get();
		++(*counter);
	}
	template<typename Other> void _assign(const shared_ptr<Other,Deleter>& r)
	{
		counter = r.counter;
		ptr = r.get();
		++(*counter);
	}
private:
	pointer        ptr;
	counter_type*  counter;
};

template<typename T, template<typename> class D> bool operator! (const shared_ptr<T,D>& s)
{
	return !s.get();
}

template<typename T, template<typename> class D> bool operator< (const shared_ptr<T,D>& l, const shared_ptr<T,D>& r)
{
	return l.get() < r.get();
}

template<typename T, template<typename> class D> bool operator== (const shared_ptr<T,D>& l, const shared_ptr<T,D>& r)
{
	return l.get() == r.get();
}

template<typename T, template<typename> class D> bool operator!= (const shared_ptr<T,D>& l, const shared_ptr<T,D>& r)
{
	return !(l == r);
}

template<typename T, template<typename> class D> std::ostream& operator<< (std::ostream& s, const shared_ptr<T,D>& r)
{
	return s << r.get();
}

template<typename T, typename U, template<typename> class D> shared_ptr<T,D> dynamic_pointer_cast(const shared_ptr<U,D>& s)
{
	return shared_ptr<T,D>(s, detail::dynamic_cast_tag());
}

template<typename T, typename U, template<typename> class D> shared_ptr<T,D> static_pointer_cast(const shared_ptr<U,D>& s)
{
	return shared_ptr<T,D>(s, detail::static_cast_tag());
}

}

#endif
