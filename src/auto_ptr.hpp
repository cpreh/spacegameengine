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


#ifndef SGE_AUTO_PTR_HPP_INCLUDED
#define SGE_AUTO_PTR_HPP_INCLUDED

#include <boost/utility.hpp>
#include "./smart_ptr_policies.hpp"

namespace sge
{

template<typename T, template <typename> class Deleter = heap_deleter> class auto_ptr : boost::noncopyable, Deleter<T> {
public:
	typedef T& reference;
	typedef T* pointer;
	explicit auto_ptr(pointer p = 0) : p(p) {}
	~auto_ptr() { _destroy(); }
	auto_ptr& operator=(pointer np) { _destroy(); p = np; return *this; }
	pointer operator->() const { return p; }
	reference operator*() const { return *p; }
	pointer get() const { return p; }
	void reset(pointer np = 0) { _destroy(); p = np; }
	bool operator!() const { return p; }
	operator bool() const { return p; }
private:
	auto_ptr(const auto_ptr&);
	void _destroy() { delete_(p); }
	pointer p;
};

template<typename T> bool operator==(const auto_ptr<T>& l, const auto_ptr<T>& r) { return l.get() == r.get(); }
template<typename T> bool operator!=(const auto_ptr<T>& l, const auto_ptr<T>& r) { return !(l==r); }

}

#endif
