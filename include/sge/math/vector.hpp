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


#ifndef SGE_MATH_VECTOR_HPP_INCLUDED
#define SGE_MATH_VECTOR_HPP_INCLUDED

#include "../config.h"
#include "compare.hpp"
#include "mod.hpp"
#include "../exception.hpp"
#include "../text.hpp"
#include "../assert.hpp"
#include "../exception.hpp"
#ifndef SGE_HAVE_VARIADIC_TEMPLATES
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#endif
#include <boost/static_assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <iterator>
#include <istream>
#include <ostream>
#include <cstddef>
#include <cmath>

#ifndef SGE_HAVE_VARIADIC_TEMPLATES
#ifndef SGE_MATH_VECTOR_MAX_SIZE
#define SGE_MATH_VECTOR_MAX_SIZE 4
#endif
#endif

namespace sge
{
namespace math
{

/** 
 * This class should be used for representing vectors, so either points or
 * direction vectors. You could also store size values in here, but there are
 * no accessors like "w" or "h". Use sge::math::rect or
 * sge::math::dim for that purpose.
 *
 * vector uses C++0x variadic templates where available.
 */
template<typename T, std::size_t Dim>
class vector {
#ifndef SGE_HAVE_VARIADIC_TEMPLATES
	BOOST_STATIC_ASSERT(Dim <= SGE_MATH_VECTOR_MAX_SIZE);
#endif
public:
	typedef T              value_type;
	typedef T&             reference;
	typedef const T&       const_reference;
	typedef std::ptrdiff_t difference_type;
	typedef std::size_t    size_type;
	typedef T*             pointer;
	typedef const T*       const_pointer;
	typedef pointer        iterator;
	typedef const_pointer  const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	explicit vector() {}

#ifdef SGE_HAVE_VARIADIC_TEMPLATES
	template<typename... Args>
	explicit vector(Args... args)
	{
		BOOST_STATIC_ASSERT(sizeof...(args) == Dim);
		set(args...);
	}
#else
#define SGE_MATH_VECTOR_CTOR_ASSIGN_N(z, n, text) (*this)[n] = text##n;
#define SGE_MATH_VECTOR_CTOR(z, n, text) vector(BOOST_PP_ENUM_PARAMS(BOOST_PP_ADD(n,1), T const& param)) { BOOST_STATIC_ASSERT(BOOST_PP_ADD(n,1)==Dim); BOOST_PP_REPEAT(BOOST_PP_ADD(n,1), SGE_MATH_VECTOR_CTOR_ASSIGN_N, param) }
	BOOST_PP_REPEAT(SGE_MATH_VECTOR_MAX_SIZE, SGE_MATH_VECTOR_CTOR, void)
#endif

	static vector const
	null()
	{
		vector ret;
		
		for(size_type i = 0; i < Dim; ++i)
			ret[i] = static_cast<value_type>(0);
		return ret;
	}

	/**
	 * This constructor gets a vector of the same type, but with a dimension
	 * lower. This is just a convenience so you can construct, for example, a
	 * vector3 from a vector2 by writing \code vector<T,2> small;
	 * vector<T,3> large(small,0); \endcode
	 */
	template<std::size_t U>
	vector(const vector<T,U>& v, typename boost::enable_if_c<U == Dim - 1, const_reference>::type n = 0)
	{
		for(size_type i = 0; i < U; ++i)
			data_[i] = v[i];
		data_[U] = n;
	}

	vector(const vector& r)
	{
		for(size_type i = 0; i < Dim; ++i)
			data_[i] = r[i];
	}

	vector& operator=(const vector& r)
	{
		for(size_type i = 0; i < Dim; ++i)
			data_[i] = r[i];
		return *this;
	}

	vector& operator+=(const vector& r)
	{
		for(size_type i = 0; i < Dim; ++i)
			data_[i] += r[i];
		return *this;
	}

	vector& operator-=(const vector& r)
	{
		for(size_type i = 0; i < Dim; ++i)
			data_[i] -= r[i];
		return *this;
	}

	vector operator+(const vector& r) const
	{
		return vector(*this) += r;
	}

	vector operator-(const vector& r) const
	{
		return vector(*this) -= r;
	}

	vector operator+() const
	{
		vector ret;
		for(size_type i = 0; i < Dim; ++i)
			ret[i] = +data_[i];
		return ret;
	}

	vector operator-() const
	{
		vector ret;
		for(size_type i = 0; i < Dim; ++i)
			ret[i] = -data_[i];
		return ret;
	}

	/**
	 * Scalar multiplication
	 */
	vector& operator*=(const_reference r)
	{
		for(size_type i = 0; i < Dim; ++i)
			(*this)[i] *= r;
		return *this;
	}

	/**
	 * This does not take the dot or cross product but rather multiplies componentwise
	 */
	vector& operator*=(const vector& r)
	{
		for(size_type i = 0; i < Dim; ++i)
			(*this)[i] *= r[i];
		return *this;
	}

	/**
	 * Scalar multiplication
	 */
	vector operator*(const_reference r) const
	{
		return vector(*this) *= r;
	}

	/**
	 * This does not take the dot or cross product but rather multiplies componentwise
	 */
	vector operator*(const vector& r) const
	{
		return vector(*this) *= r;
	}

	/**
	 * Scalar multiplication
	 */
	friend vector operator*(const_reference l, vector r)
	{
		return r *= l;
	}

	vector& operator/=(const_reference r)
	{
		for(size_type i = 0; i < Dim; ++i)
			(*this)[i] /= r;
		return *this;
	}

	vector& operator/=(const vector& r)
	{
		for(size_type i = 0; i < Dim; ++i)
			(*this)[i] /= r[i];
		return *this;
	}

	vector operator/(const_reference r) const
	{
		return vector(*this) /= r;
	}

	vector operator/(const vector& r) const
	{
		return vector(*this) /= r;
	}

	/**
	 * This operator uses sge::math::mod to calculate the modulo
	 */
	vector& operator%=(const_reference r)
	{
		for(size_type i = 0; i < Dim; ++i)
			mod_assign((*this)[i], r);
		return *this;
	}

	/**
	 * This operator uses sge::math::mod to calculate the modulo
	 */
	vector& operator%=(const vector& r)
	{
		for(size_type i = 0; i < Dim; ++i)
			mod_assign((*this)[i], r[i]);
		return *this;
	}

	/**
	 * This operator uses sge::math::mod to calculate the modulo
	 */
	vector operator%(const_reference r) const
	{
		return vector(*this) %= r;
	}

	/**
	 * This operator uses sge::math::mod to calculate the modulo
	 */
	vector operator%(const vector& r) const
	{
		return vector(*this) %= r;
	}

	value_type dot(const vector& r) const
	{
		value_type ret(0);
		for(size_type i = 0; i < Dim; ++i)
			ret += (*this)[i] * r[i];
		return ret;
	}

	/**
	 * Does range checking with an assertion
	 */
	reference operator[](const size_type pos)
	{
		SGE_ASSERT(pos < Dim);
		return data_[pos];
	}

	/**
	 * Does range checking with an assertion
	 */
	const_reference operator[](const size_type pos) const
	{
		SGE_ASSERT(pos < Dim);
		return data_[pos];
	}

	/**
	 * \throw sge::exception If argument greater than dimension
	 */
	reference at(const size_type pos)
	{
		if(pos >= Dim)
			throw exception(SGE_TEXT("vector<T, N>::at(): out of range!"));
		return data_[pos];
	}

	/**
	 * \throw sge::exception If argument greater than dimension
	 */
	const_reference at(const size_type pos) const
	{
		if(pos >= Dim)
			throw exception(SGE_TEXT("vector<T, N>::at(): out of range!"));
		return data_[pos];
	}

	/**
	 * Uses sge::math::compare to compare componentwise
	 */
	bool operator==(const vector& r) const
	{
		for(size_type i = 0; i < Dim; ++i)
			if(!compare(data_[i], r[i]))
				return false;
		return true;
	}

	/**
	 * Uses sge::math::compare to compare componentwise
	 */
	bool operator!=(const vector& r) const
	{
		return !((*this)==r);
	}

	/**
	 * Returns the dot product of the vector with itself
	 */
	value_type length_quad() const
	{
		return dot(*this);
	}

	/**
	 * Applies std::sqrt to length_quad.
	 */
	value_type length() const
	{
		return static_cast<value_type>(
			std::sqrt(
				static_cast<long double>(
					length_quad())));
	}

	/**
	 * Returns the normalized vector
	 */
	vector unit() const
	{
		SGE_ASSERT(!is_null());
		return (*this) * (static_cast<T>(1) / length());
	}

	vector& normalize()
	{
		return *this = unit();
	}

	reference x()
	{
		return (*this)[0];
	}

	const_reference x() const
	{
		return (*this)[0];
	}

	reference y()
	{
		return (*this)[1];
	}

	const_reference y() const
	{
		return (*this)[1];
	}

//	template<typename Dummy>
	reference z(/*typename boost::enable_if_c<(Dim > 2), Dummy>* = 0*/)
	{
		SGE_ASSERT(Dim > 2);
		return (*this)[2];
	}

//	template<typename Dummy>
	const_reference z(/*typename boost::enable_if_c<(Dim > 2), Dummy>* = 0*/) const
	{
		SGE_ASSERT(Dim > 2);
		return (*this)[2];
	}

	reference w()
	{
		SGE_ASSERT(Dim > 3);
		return (*this)[3];
	}

	const_reference w() const
	{
		SGE_ASSERT(Dim > 3);
		return (*this)[3];
	}

	//template<typename OtherT>
	//vector cross(const vector& r, typename boost::enable_if<boost::mpl::and_<boost::is_same<T,OtherT>, boost::mpl::bool_<Dim == 3> > >::type* = 0) const
	vector cross(const vector& r) const
	{
		return vector(y()*r.z() - z()*r.y(),
		              z()*r.x() - x()*r.z(),
		              x()*r.y() - y()*r.x());
	}

	/** 
	 * Compares the vector against the default constructed (and thus "nullified")
	 * vector
	 */
	bool is_null() const
	{
		return *this == null();
	}

	void swap(vector& r)
	{
		std::swap(*this,r);
	}

#ifdef SGE_HAVE_VARIADIC_TEMPLATES
	template<typename... Args>
	void set(const_reference arg, Args... args)
	{
		BOOST_STATIC_ASSERT(sizeof...(args) == Dim - 1);
		set_impl(0, arg, args...);
	}
private:
	template<typename... Args>
	void set_impl(const size_type i, const_reference arg, Args... args)
	{
		(*this)[i] = arg;
		set_impl(i+1, args...);
	}

	void set_impl(const size_type i, const_reference arg)
	{
		(*this)[i] = arg;
	}
public:
#else
#define SGE_MATH_VECTOR_SET(z, n, text) void set(BOOST_PP_ENUM_PARAMS(BOOST_PP_ADD(n,1), T const& param)) { BOOST_STATIC_ASSERT(BOOST_PP_ADD(n,1)==Dim); BOOST_PP_REPEAT(BOOST_PP_ADD(n,1), SGE_MATH_VECTOR_CTOR_ASSIGN_N, param) }
BOOST_PP_REPEAT(SGE_MATH_VECTOR_MAX_SIZE, SGE_MATH_VECTOR_SET, void)
#endif

	bool nearly_equals(const vector& r, const value_type& radius) const
	{
		const vector tmp(*this - r);
		return dot(tmp,tmp) < radius * radius;
	}

	size_type size() const
	{
		return Dim;
	}

	size_type dim() const
	{
		return Dim;
	}

	iterator begin()
	{
		return data_;
	}

	iterator end()
	{
		return &data_[Dim];
	}

	const_iterator begin() const
	{
		return data_;
	}

	const_iterator end() const
	{
		return &data_[Dim];
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}

	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	}

	const_reverse_iterator rbegin() const
	{
		return reverse_iterator(end());
	}

	const_reverse_iterator rend() const
	{
		return reverse_iterator(begin());
	}

	pointer data()
	{
		return data_;
	}

	const_pointer data() const
	{
		return data_;
	}
private:
	T data_[Dim];
};

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
