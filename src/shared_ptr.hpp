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

#include <boost/shared_ptr.hpp>
#include "heap_deleter.hpp"

namespace sge
{

using boost::weak_ptr;

template<typename T, template<typename> class Deleter = heap_deleter>
class shared_ptr {
public:
	typedef boost::shared_ptr<T> impl_type;
	typedef typename impl_type::element_type element_type;
	typedef typename impl_type::value_type value_type;
	typedef typename impl_type::pointer pointer;
	typedef typename impl_type::reference reference;

	shared_ptr()
	{}

	// FIXME: dangerous
	template<typename U>
	explicit shared_ptr(const boost::shared_ptr<U>& p)
	: impl(p)
	{}

	template<class Y>
	explicit shared_ptr( Y *const p )
	: impl(p, deleter())
	{}

	template<class Y, class D, class A> shared_ptr( Y *const p, const A& a )
	: impl(p, deleter(), a)
	{}

	template<class Y>
	explicit shared_ptr(weak_ptr<Y> const & r)
	: impl(r)
	{}

	template<class Y>
	shared_ptr(shared_ptr<Y> const & r)
	: impl(r.get_boost_ptr())
	{}

	template<class Y>
	shared_ptr(shared_ptr<Y> const & r, boost::detail::static_cast_tag)
	: impl(r.get_boost_ptr(), boost::detail::static_cast_tag())
	{}

	template<class Y>
	shared_ptr(shared_ptr<Y> const & r, boost::detail::const_cast_tag)
	: impl(r.get_boost_ptr(), boost::detail::const_cast_tag())
	{}

	template<class Y>
	shared_ptr(shared_ptr<Y> const & r, boost::detail::dynamic_cast_tag)
	: impl(r.get_boost_ptr(), boost::detail::dynamic_cast_tag())
	{}

	template<class Y>
	shared_ptr(shared_ptr<Y> const & r, boost::detail::polymorphic_cast_tag)
	: impl(r.get_boost_ptr(), boost::detail::polymorphic_cast_tag())
	{}
#ifndef BOOST_NO_AUTO_PTR

	template<class Y>
	explicit shared_ptr(std::auto_ptr<Y> & r)
	: impl(r)
	{}

	/*template<class Ap>
	explicit shared_ptr( Ap r, typename boost::detail::sp_enable_if_auto_ptr<Ap, int>::type = 0 )
	: impl(r)
	{}*/


#endif // BOOST_NO_AUTO_PTR

	template<class Y>
	shared_ptr & operator=(shared_ptr<Y> const & r)
	{
		impl = r.impl;
		return *this;
	}

#ifndef BOOST_NO_AUTO_PTR

	template<class Y>
	shared_ptr & operator=( std::auto_ptr<Y> & r )
	{
 		impl = r;
		return *this;
	}

	/*template<class Ap>
	typename boost::detail::sp_enable_if_auto_ptr< Ap, shared_ptr & >::type operator=( Ap r )
	{
		impl = a.
		this_type( r ).swap( *this );
		 return *this;
	}*/


#endif // BOOST_NO_AUTO_PTR

	void reset() // never throws in 1.30+
	{
		impl.reset();
	}

	template<class Y> void reset(Y *const p) // Y must be complete
	{
        	impl.reset(p, deleter());
	}

	template<class Y, class A> void reset( Y *const p, const A& a )
	{
		impl.reset(p, deleter(), a);
	}

	reference operator* () const // never throws
	{
		return *impl;
	}

	pointer operator-> () const // never throws
	{
		return impl.operator->();
	}
    
	pointer get() const // never throws
	{
        	return impl.get();
	}

	typedef typename impl_type::unspecified_bool_type unspecified_bool_type;

	operator unspecified_bool_type() const // never throws
	{
		return impl;
	}

	bool operator! () const // never throws
	{
		return !impl;
	}

	bool unique() const // never throws
	{
		return impl.unique();
	}

	long use_count() const // never throws
	{
		return impl.use_count();
	}

	void swap(shared_ptr<T> & other) // never throws
	{
		std::swap(impl, other.impl);
 	}

	const impl_type& get_boost_ptr() const
	{
		return impl;
	}
private:
	impl_type impl;

	static Deleter<T> deleter()
	{
		return Deleter<T>();
	}
	
	template<typename Other, template<typename> class OtherDeleter> friend class shared_ptr;
};

template<class T, class U> inline bool operator==(shared_ptr<T> const & a, shared_ptr<U> const & b)
{
	return a.get_boost_ptr() == b.get_boost_ptr();
}

template<class T, class U> inline bool operator!=(shared_ptr<T> const & a, shared_ptr<U> const & b)
{
	return !(a==b);
}

template<class T, class U> inline bool operator<(shared_ptr<T> const & a, shared_ptr<U> const & b)
{
	return a.get_boost_ptr() < b.get_boost_ptr();
}

template<class T> inline void swap(shared_ptr<T> & a, shared_ptr<T> & b)
{
	a.swap(b);
}

template<class T, class U> shared_ptr<T> static_pointer_cast(shared_ptr<U> const & r)
{
	return shared_ptr<T>(r, boost::detail::static_cast_tag());
}

template<class T, class U> shared_ptr<T> const_pointer_cast(shared_ptr<U> const & r)
{
	return shared_ptr<T>(r, boost::detail::const_cast_tag());
}

template<class T, class U> shared_ptr<T> dynamic_pointer_cast(shared_ptr<U> const & r)
{
	return shared_ptr<T>(r, boost::detail::dynamic_cast_tag());
}

template<typename T, typename U> shared_ptr<T> polymorphic_pointer_cast(const shared_ptr<U>& r)
{
	return shared_ptr<T>(r, boost::detail::polymorphic_cast_tag());
}

template<class T> inline T * get_pointer(shared_ptr<T> const & p)
{
    return p.get();
}

template<class E, class T, class Y> std::basic_ostream<E, T> & operator<< (std::basic_ostream<E, T> & os, shared_ptr<Y> const & p)
{
    os << p.get();
    return os;
}

}

#endif
