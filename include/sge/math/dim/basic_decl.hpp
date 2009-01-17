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


#ifndef SGE_MATH_DIM_BASIC_DECL_HPP_INCLUDED
#define SGE_MATH_DIM_BASIC_DECL_HPP_INCLUDED

#include "../detail/make_op_decl.hpp"
#include "../detail/make_variadic_constructor_decl.hpp"
#include "../detail/array_adapter.hpp"
#include <iterator>

#ifndef SGE_MATH_DIM_MAX_CTOR_PARAMS
#define SGE_MATH_DIM_MAX_CTOR_PARAMS 3
#endif

namespace sge
{
namespace math
{
namespace dim
{

template<
	typename T,
	typename N,
	typename S
>
class basic
: array_adapter<basic<T, N, S> > {
public:
	typedef typename N::value_type size_type;
	typedef T value_type;
	typedef T &reference;
	typedef T const &const_reference;
	typedef T *pointer;
	typedef T const *const_pointer;
	typedef pointer iterator;
	typedef const_pointer  const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	basic();

	template<
		typename In
	>
	basic(
		In beg,
		In end);

#define SGE_MATH_DETAIL_MAKE_VARIADIC_CONSTRUCTOR_MAX_SIZE SGE_MATH_DIM_MAX_CTOR_PARAMS
	SGE_MATH_DETAIL_MAKE_VARIADIC_CONSTRUCTOR_DECL(basic)
#undef SGE_MATH_DETAIL_MAKE_VARIADIC_CONSTRUCTOR_MAX_SIZE

	reference
	operator[](
		size_type);

	const_reference
	operator[](
		size_type) const;
	
	pointer data();
	const_pointer data() const;
	
	size_type size() const;
	
	reference w();
	const_reference w() const;
	reference h();
	const_reference h() const;
	reference d();
	const_reference d() const;

	size_type content() const;
//	{
//		return std::accumulate(begin(), end(), 1, std::multiplies<size_type>());
//	}

	static dim const
	null();
private:
	S storage;
};

#if 0

template<typename T, std::size_t Dim, typename Ch, typename Traits>
std::basic_ostream<Ch,Traits> &operator<<(std::basic_ostream<Ch,Traits> &stream,const dim<T,Dim> &v)
{
	stream << stream.widen('(');
	for(typename dim<T,Dim>::size_type i = 0; i < Dim-1; ++i)
		stream << v[i] << stream.widen(',');
	return stream << v[Dim-1] << stream.widen(')');
}

template<typename T, std::size_t Dim, typename Ch, typename Traits>
std::basic_istream<Ch,Traits>& operator>>(std::basic_istream<Ch,Traits>& s, dim<T,Dim>& v)
{
	Ch c;
	s >> c;
	if(c != s.widen('('))
		s.setstate(std::ios_base::failbit);
	for(typename dim<T,Dim>::size_type i = 0; i < Dim-1; ++i)
	{
		s >> v[i] >> c;
		if (c != s.widen(','))
			s.setstate(std::ios_base::failbit);
	}
	s >> v[Dim-1] >> c;
	if (c != s.widen(')'))
		s.setstate(std::ios_base::failbit);
	return s;
}

#endif

}
}
}

#endif

