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


#ifndef SGE_MATH_VECTOR_BASIC_DECL_HPP_INCLUDED
#define SGE_MATH_VECTOR_BASIC_DECL_HPP_INCLUDED

#include "../detail/make_op_decl.hpp"

namespace sge
{
namespace math
{

#define SGE_MATH_VECTOR_BASIC_DECLARE_OPERATOR(op)\
SGE_MATH_DETAIL_MAKE_OP_DECL(basic, op)

template<
	typename T,
	typename N,
	typename S
>
struct basic {
	typedef typename N::value_type size_type;
	typedef T value_type;
	typedef T &reference;
	typedef T const &const_reference;
	typedef T *pointer;
	typedef T const *const_pointer;
	typedef pointer iterator;
	typedef const_pointer const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	basic();
#ifndef SGE_MATH_DETAIL_MAKE_VARIADIC_CONSTRUCTOR_MAX_SIZE
#define SGE_MATH_DETAIL_MAKE_VARIADIC_CONSTRUCTOR_MAX_SIZE 4
	SGE_MATH_DETAIL_MAKE_VARIADIC_CONSTRUCTOR(basic)
#undef SGE_MATH_DETAIL_MAKE_VARIADIC_CONSTRUCTOR_MAX_SIZE

	SGE_MATH_VECTOR_BASIC_DECLARE_OPERATOR(+=)
	SGE_MATH_VECTOR_BASIC_DECLARE_OPERATOR(-=)
	SGE_MATH_VECTOR_BASIC_DECLARE_OPERATOR(*=)
	SGE_MATH_VECTOR_BASIC_DECLARE_OPERATOR(/=)
	SGE_MATH_VECTOR_BASIC_DECLARE_OPERATOR(%=)

	const_reference
	operator[](
		size_type) const;

	reference
	operator[](
		size_type);

	const_reference
	at(
		size_type) const;
	
	reference
	at(
		size_type);
	
	pointer data();
	const_pointer data() const;
	
	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;
	reverse_iterator rbegin();
	const_reverse_iterator rbegin() const;
	reverse_iterator rend();
	const_reverse_iterator rend() const;

	size_type size() const;
	bool empty() const;

	static basic const
	null();

	reference x();
	const_reference x() const;
	reference y();
	const_reference y() const;
	reference z();
	const_reference z() const;
	reference w();
	const_reference w() const;

	void resize(
		size_type);
private:
	void initial_size(
		size_type);
	
	S storage;
};

}
}

#endif

#if 0
template<typename T, std::size_t Dim>
void place(vector<T,Dim>& v,
           const typename vector<T,Dim>::const_reference radius,
           const typename vector<T,Dim>::const_reference high_angle,
           const typename vector<T,Dim>::const_reference plane_angle,
           typename boost::enable_if_c<Dim==3,T>::type* = 0)
{
	v.x() = radius * std::sin(high_angle) * std::cos(plane_angle);
	v.z() = radius * std::sin(high_angle) * std::sin(plane_angle);
	v.y() = radius * std::cos(high_angle);
}

template<typename T, std::size_t Dim>
void swap(vector<T,Dim>& a, vector<T,Dim>& b)
{
	a.swap(b);
}

template<typename T, std::size_t Dim>
vector<T,Dim> cross(const vector<T,Dim>& l, const vector<T,Dim>& r)
{
	return l.cross(r);
}

template<typename T, std::size_t Dim>
vector<T,Dim> normalize(vector<T,Dim> l)
{
	return l.normalize();
}

template<typename T, std::size_t Dim>
typename vector<T,Dim>::value_type dot(const vector<T,Dim>& l, const vector<T,Dim>& r)
{
	return l.dot(r);
}

/**
 * Outputs the vector in the format \f$(v_0,\ldots,v_n)\f$.
 */
template<typename T, std::size_t Dim,typename Ch, typename Traits>
inline std::basic_ostream<Ch,Traits>& operator<< (std::basic_ostream<Ch,Traits>& s, const vector<T,Dim>& v)
{
	s << s.widen('(');
	for(typename vector<T,Dim>::size_type i = 0; i < Dim-1; ++i)
		s << v[i] << s.widen(',');
	return s << v[Dim-1] << s.widen(')');
}

/**
 * Reads the vector from the stream in the format \f$(v_0,\ldots,v_n)\f$.
 */
template<typename T, std::size_t Dim,typename Ch, typename Traits>
std::basic_istream<Ch,Traits>& operator>> (std::basic_istream<Ch,Traits>& s, vector<T,Dim>& v)
{
	Ch c;
	s >> c;
	if(c != s.widen('('))
		s.setstate(std::ios_base::failbit);
	for(typename vector<T,Dim>::size_type i = 0; i < Dim-1; ++i)
	{
		s >> v[i] >> c;
		if(c != s.widen(','))
			s.setstate(std::ios_base::failbit);
	}
	s >> v[Dim-1] >> c;
	if(c != s.widen(')'))
		s.setstate(std::ios_base::failbit);
	return s;
}

/**
 * Casts the vector<T> to vector<D> (using static_cast).
 */
template<typename D, typename S, std::size_t Dim>
vector<D, Dim> structure_cast(const vector<S, Dim>& s)
{
	typedef vector<D, Dim> ret_type;
	ret_type ret;
	for(typename ret_type::size_type i = 0; i < Dim; ++i)
		ret[i] = static_cast<D>(s[i]);
	return ret;
}

}
}

#endif
