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

#include "basic_fwd.hpp"
#include "../detail/make_op_decl.hpp"
#include "../detail/make_variadic_constructor_decl.hpp"
#include "../detail/array_adapter.hpp"
#include <sge/type_traits/is_iterator.hpp>
#include <boost/utility/enable_if.hpp>

#ifndef SGE_MATH_VECTOR_MAX_CTOR_PARAMS
#define SGE_MATH_VECTOR_MAX_CTOR_PARAMS 4
#endif

namespace sge
{
namespace math
{
namespace vector
{
namespace detail
{

template<
	typename T,
	typename N,
	typename S
>
struct typedef_helper {
	typedef math::detail::array_adapter<
		basic<
			T,
			N,
			S
		>,
		T,
		typename N::value_type
	> type;
};

}

template<
	typename T,
	typename N,
	typename S
>
class basic
: public detail::typedef_helper<T, N, S>::type {
	typedef typename detail::typedef_helper<T, N, S>::type base;
public:
	typedef S storage_type;

	typedef typename base::size_type size_type;
	typedef typename base::value_type value_type;
	typedef typename base::reference reference;
	typedef typename base::const_reference const_reference;
	typedef typename base::pointer pointer;
	typedef typename base::const_pointer const_pointer;
	typedef typename base::iterator iterator;
	typedef typename base::const_iterator const_iterator;
	typedef typename base::reverse_iterator reverse_iterator;
	typedef typename base::const_reverse_iterator const_reverse_iterator;

	basic();

	explicit basic(
		storage_type const &);

	template<
		typename In
	>
	basic(
		In beg,
		typename boost::enable_if<
			is_iterator<
				In
			>,
			In
		>::type end);

#define SGE_MATH_DETAIL_MAKE_VARIADIC_CONSTRUCTOR_MAX_SIZE SGE_MATH_VECTOR_MAX_CTOR_PARAMS
	SGE_MATH_DETAIL_MAKE_VARIADIC_CONSTRUCTOR_DECL(basic)
#undef SGE_MATH_DETAIL_MAKE_VARIADIC_CONSTRUCTOR_MAX_SIZE
public:

#define SGE_MATH_VECTOR_BASIC_DECLARE_OPERATOR(op)\
SGE_MATH_DETAIL_MAKE_OP_DECL(basic, op)
	SGE_MATH_VECTOR_BASIC_DECLARE_OPERATOR(+=)
	SGE_MATH_VECTOR_BASIC_DECLARE_OPERATOR(-=)
	SGE_MATH_VECTOR_BASIC_DECLARE_OPERATOR(*=)
	SGE_MATH_VECTOR_BASIC_DECLARE_OPERATOR(/=)
	SGE_MATH_VECTOR_BASIC_DECLARE_OPERATOR(%=)
#undef SGE_MATH_VECTOR_BASIC_DECLARE_OPERATOR

	basic &
	operator*=(
		value_type const &);
	
	basic &
	operator/=(
		value_type const &);

	const_reference
	operator[](
		size_type) const;

	reference
	operator[](
		size_type);

	pointer data();
	const_pointer data() const;
	
	size_type size() const;

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
	S storage;
};

}
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

#endif
