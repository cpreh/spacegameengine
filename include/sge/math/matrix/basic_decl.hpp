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


#ifndef SGE_MATH_MATRIX_BASIC_DECL_HPP_INCLUDED
#define SGE_MATH_MATRIX_BASIC_DECL_HPP_INCLUDED

#include "basic_fwd.hpp"
#include "detail/typedef_helper.hpp"
#include "detail/dim_storage.hpp"
#include "../detail/make_op_decl.hpp"
#include "../detail/make_variadic_constructor_decl.hpp"
#include "../dim/static.hpp"
#include <boost/type_traits/is_same.hpp>
#include <boost/static_assert.hpp>

#ifndef SGE_MATH_MATRIX_MAX_CTOR_PARAMS
#define SGE_MATH_MATRIX_MAX_CTOR_PARAMS 16
#endif

namespace sge
{
namespace math
{
namespace matrix
{

template<
	typename T,
	typename N,
	typename M,
	typename S
>
class basic
:
	public detail::typedef_helper<T, N, M, S>::type,
	detail::dim_storage<N, M>
{
	typedef typename detail::typedef_helper<T, N, M, S>::type base;
	typedef detail::dim_storage<N, M> dim_base;
public:
	BOOST_STATIC_ASSERT((
		boost::is_same<
			typename N::value_type,
			typename M::value_type
		>::value));

	typedef N dim_wrapper;
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

	typedef typename dim::static_<size_type, 2>::type dim_type;

	basic();

	template<
		typename In
	>
	basic(
		In beg,
		In end);

	template<
		typename Container
	>
	basic(
		dim_type const &,
		Container const &);

#define SGE_MATH_DETAIL_MAKE_VARIADIC_CONSTRUCTOR_MAX_SIZE SGE_MATH_MATRIX_MAX_CTOR_PARAMS
	SGE_MATH_DETAIL_MAKE_VARIADIC_CONSTRUCTOR_DECL(basic)
#undef SGE_MATH_DETAIL_MAKE_VARIADIC_CONSTRUCTOR_MAX_SIZE

#define SGE_MATH_MATRIX_BASIC_DECLARE_OPERATOR(op)\
SGE_MATH_DETAIL_MAKE_OP_DECL(basic, op)
	SGE_MATH_MATRIX_BASIC_DECLARE_OPERATOR(+=)
	SGE_MATH_MATRIX_BASIC_DECLARE_OPERATOR(-=)
#undef SGE_MAT_MATRIX_BASIC_DECLARE_OPERATOR
public:
	reference
	operator[](
		size_type);
	
	const_reference const
	operator[](
		size_type) const;
	
	pointer data();
	const_pointer data() const;

	size_type size() const;

	size_type rows() const;
	size_type columns() const;

	static basic const
	identity();

	void resize(
		dim_type const &);
private:
	S storage;
};

}
}
}

#endif
