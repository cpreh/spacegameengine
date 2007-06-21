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

//#include <ostream>
//#include <cstddef>
//#include <functional>
#include <boost/shared_ptr.hpp>
#include "heap_deleter.hpp"
//#include "ptr_cast.hpp"

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

	template<class Y>
	explicit shared_ptr( Y * p )
	: impl(p, deleter())
	{}

    //
    // Requirements: D's copy constructor must not throw
    //
    // shared_ptr will release p by calling d(p)
    //

/*    template<class Y, class D> shared_ptr(Y * p, D d): px(p), pn(p, d)
    {
        boost::detail::sp_enable_shared_from_this( pn, p, p );
    }*/

    // As above, but with allocator. A's copy constructor shall not throw.

/*    template<class Y, class D, class A> shared_ptr( Y * p, D d, A a ): px( p ), pn( p, d, a )
    {
        boost::detail::sp_enable_shared_from_this( pn, p, p );
    }*/

//  generated copy constructor, assignment, destructor are fine...

//  except that Borland C++ has a bug, and g++ with -Wsynth warns
/*#if defined(__BORLANDC__) || defined(__GNUC__)

    shared_ptr & operator=(shared_ptr const & r) // never throws
    {
        px = r.px;
        pn = r.pn; // shared_count::op= doesn't throw
        return *this;
    }

#endif*/

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

/*#if !defined( BOOST_NO_SFINAE ) && !defined( BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION )

    template<class Ap>
    explicit shared_ptr( Ap r, typename boost::detail::sp_enable_if_auto_ptr<Ap, int>::type = 0 ): px( r.get() ), pn()
    {
        typename Ap::element_type * tmp = r.get();
        pn = boost::detail::shared_count( r );
        boost::detail::sp_enable_shared_from_this( pn, tmp, tmp );
    }


#endif // BOOST_NO_SFINAE, BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION*/

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

/*#if !defined( BOOST_NO_SFINAE ) && !defined( BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION )

    template<class Ap>
    typename boost::detail::sp_enable_if_auto_ptr< Ap, shared_ptr & >::type operator=( Ap r )
    {
        this_type( r ).swap( *this );
        return *this;
    }


#endif // BOOST_NO_SFINAE, BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION*/

#endif // BOOST_NO_AUTO_PTR

	void reset() // never throws in 1.30+
	{
		impl.reset();
	}

	template<class Y> void reset(Y *const p) // Y must be complete
	{
        	impl.reset(p, deleter());
	}

/*	template<class Y, class D> void reset( Y * p, D d )
	{
        	this_type( p, d ).swap( *this );
	}*/

/*	template<class Y, class D, class A> void reset( Y * p, D d, A a )
	{
        	this_type( p, d, a ).swap( *this );
	}*/

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

	// implicit conversion to "bool"

	typedef typename impl_type::unspecified_bool_type unspecified_bool_type;

	operator unspecified_bool_type() const // never throws
	{
		return impl;
	}

    // operator! is redundant, but some compilers need it

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

// get_pointer() enables boost::mem_fn to recognize shared_ptr

template<class T> inline T * get_pointer(shared_ptr<T> const & p)
{
    return p.get();
}

// operator<<

/*template<class Y> std::ostream & operator<< (std::ostream & os, shared_ptr<Y> const & p)
{
    os << p.get();
    return os;
}

#else

// in STLport's no-iostreams mode no iostream symbols can be used
#ifndef _STLP_NO_IOSTREAMS

# if defined(BOOST_MSVC) && BOOST_WORKAROUND(BOOST_MSVC, < 1300 && __SGI_STL_PORT)
// MSVC6 has problems finding std::basic_ostream through the using declaration in namespace _STL
using std::basic_ostream;
template<class E, class T, class Y> basic_ostream<E, T> & operator<< (basic_ostream<E, T> & os, shared_ptr<Y> const & p)
# else*/
template<class E, class T, class Y> std::basic_ostream<E, T> & operator<< (std::basic_ostream<E, T> & os, shared_ptr<Y> const & p)
//# endif 
{
    os << p.get();
    return os;
}

//#endif // _STLP_NO_IOSTREAMS

//#endif // __GNUC__ < 3

// get_deleter (experimental)

/*#if ( defined(__GNUC__) && BOOST_WORKAROUND(__GNUC__, < 3) ) || \
    ( defined(__EDG_VERSION__) && BOOST_WORKAROUND(__EDG_VERSION__, <= 238) ) || \
    ( defined(__HP_aCC) && BOOST_WORKAROUND(__HP_aCC, <= 33500) )

// g++ 2.9x doesn't allow static_cast<X const *>(void *)
// apparently EDG 2.38 and HP aCC A.03.35 also don't accept it

template<class D, class T> D * get_deleter(shared_ptr<T> const & p)
{
    void const * q = p._internal_get_deleter(typeid(D));
    return const_cast<D *>(static_cast<D const *>(q));
}

#else

template<class D, class T> D * get_deleter(shared_ptr<T> const & p)
{
    return static_cast<D *>(p._internal_get_deleter(typeid(D)));
}*/
/*namespace detail {

struct static_cast_tag{};
struct dynamic_cast_tag{};

typedef std::size_t shared_counter_type;

}
	
template<typename T, template <typename> class Deleter = heap_deleter> class shared_ptr : Deleter<T> {
public:
	typedef T        value_type;
	typedef T&       reference;
	typedef const T& const_reference;
	typedef T*       pointer;
	typedef const T* const_pointer;
	
	shared_ptr()
	 : ptr(0),
	   counter(new detail::shared_counter_type(1)) {}

	explicit shared_ptr(const pointer p)
	 : ptr(p),
	   counter(new detail::shared_counter_type(1)) {}

	shared_ptr(const shared_ptr& r) { _assign(r); }
	template<typename Other> shared_ptr(const shared_ptr<Other,Deleter>& r) { _assign(r); }
	template<typename Other> shared_ptr(const shared_ptr<Other,Deleter>& r, detail::dynamic_cast_tag)
	 : ptr(ptr_cast<pointer>(r.get()))
	{
		_copy_counter(r.counter);
	}
	template<typename Other> shared_ptr(const shared_ptr<Other,Deleter>& r, detail::static_cast_tag)
	 : ptr(static_cast<pointer>(r.get()))
	{
		_copy_counter(r.counter);
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
		if(p == get())
			return;
		
		_release();
		ptr = p;
		counter = new detail::shared_counter_type(1);
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

	void _copy_counter(detail::shared_counter_type* const c)
	{
		counter = c;
		++(*counter);
	}

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

	template<typename Other> void _assign(const shared_ptr<Other,Deleter>& r)
	{
		_copy_counter(r.counter);
		ptr = r.ptr;
	}
private:
	pointer                       ptr;
	detail::shared_counter_type*  counter;
};

template<typename T, template<typename> class D> bool operator! (const shared_ptr<T,D>& s)
{
	return !s.get();
}

template<typename T, template<typename> class D> bool operator< (const shared_ptr<T,D>& l, const shared_ptr<T,D>& r)
{
	return std::less<typename shared_ptr<T,D>::const_pointer>()(l.get(), r.get());
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
}*/

}

#endif
