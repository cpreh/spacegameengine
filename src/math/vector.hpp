#ifndef SGE_MATH_VECTOR_HPP_INCLUDED
#define SGE_MATH_VECTOR_HPP_INCLUDED

#include <cassert>
#include <cstddef>
#include <iostream>
#include <cmath>
#include <iterator>
#include <boost/static_assert.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/utility/enable_if.hpp>
//#include <boost/mpl/and.hpp>
//#include <boost/mpl/bool.hpp>
//#include <boost/type_traits/is_same.hpp>
#include "../util.hpp"
#include "../exception.hpp"

#ifndef SGE_MATH_VECTOR_MAX_SIZE
#define SGE_MATH_VECTOR_MAX_SIZE 4
#endif

namespace sge
{
namespace math
{

template<typename T, std::size_t Dim>
class basic_vector {
	BOOST_STATIC_ASSERT(Dim > 1 && Dim <= SGE_MATH_VECTOR_MAX_SIZE);
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

#define SGE_MATH_VECTOR_CTOR_ASSIGN_N(z, n, text) (*this)[n] = text##n;
#define SGE_MATH_VECTOR_CTOR(z, n, text) basic_vector(BOOST_PP_ENUM_PARAMS(BOOST_PP_ADD(n,1), T const& param)) { BOOST_STATIC_ASSERT(BOOST_PP_ADD(n,1)==Dim); BOOST_PP_REPEAT(BOOST_PP_ADD(n,1), SGE_MATH_VECTOR_CTOR_ASSIGN_N, param) }
	BOOST_PP_REPEAT(SGE_MATH_VECTOR_MAX_SIZE, SGE_MATH_VECTOR_CTOR, void)

	basic_vector()
	{
		for(size_type i = 0; i < Dim; ++i)
			data_[i] = 0;
	}

	basic_vector(no_initialization_tag)
	{
	}

	template<std::size_t U>
	basic_vector(const basic_vector<T,U>& v, const_reference n = 0, typename boost::enable_if_c<U == Dim-1>::type* =0)
	{
		for(size_type i = 0; i < U; ++i)
			data_[i] = v[i];
		data_[U] = n;
	}

	basic_vector(const basic_vector& r)
	{
		for(size_type i = 0; i < Dim; ++i)
			data_[i] = r[i];
	}

	basic_vector& operator=(const basic_vector& r)
	{
		for(size_type i = 0; i < Dim; ++i)
			data_[i] = r[i];
		return *this;
	}

	basic_vector& operator+=(const basic_vector& r)
	{
		for(size_type i = 0; i < Dim; ++i)
			data_[i] += r[i];
		return *this;
	}

	basic_vector& operator-=(const basic_vector& r)
	{
		for(size_type i = 0; i < Dim; ++i)
			data_[i] -= r[i];
		return *this;
	}

	basic_vector operator+(const basic_vector& r) const
	{
		return basic_vector(*this) += r;
	}

	basic_vector operator-(const basic_vector& r) const
	{
		return basic_vector(*this) -= r;
	}

	basic_vector operator+() const
	{
		basic_vector ret = basic_vector(no_initialization_tag());
		for(size_type i = 0; i < Dim; ++i)
			ret[i] = +data_[i];
		return ret;
	}

	basic_vector operator-() const
	{
		basic_vector ret = basic_vector(no_initialization_tag());
		for(size_type i = 0; i < Dim; ++i)
			ret[i] = -data_[i];
		return ret;
	}

	value_type operator*(const basic_vector& r) const
	{
		return dot(r);
	}

	value_type dot(const basic_vector& r) const
	{
		value_type ret(0);
		for(size_type i = 0; i < Dim; ++i)
			ret += (*this)[i] * r[i];
		return ret;
	}

	basic_vector& operator*=(const_reference r)
	{
		for(size_type i = 0; i < Dim; ++i)
			(*this)[i] *= r;
		return *this;
	}

	friend basic_vector operator*(const_reference l, const basic_vector& r)
	{
		return basic_vector(r) *= l;
	}

	friend basic_vector operator*(const basic_vector& l, const_reference r)
	{
		return r * l;
	}

	reference operator[](const size_type pos)
	{
		assert(pos < Dim);
		return data_[pos];
	}

	const_reference operator[](const size_type pos) const
	{
		assert(pos < Dim);
		return data_[pos];
	}

	reference at(const size_type pos)
	{
		if(pos >= Dim)
			throw exception("basic_vector<T, N>::at(): out of range!");
		return data_[pos];
	}

	const_reference at(const size_type pos) const
	{
		if(pos >= Dim)
			throw exception("basic_vector<T, N>::at(): out of range!");
		return data_[pos];
	}

	// TODO: do something different for float here
	bool operator==(const basic_vector& r) const
	{
		for(size_type i = 0; i < Dim; ++i)
			if(data_[i] != r[i])
				return false;
		return true;
	}

	bool operator!=(const basic_vector& r) const
	{
		return !((*this)==r);
	}

	value_type length_quad() const
	{
		value_type ret(0);
		for(size_type i = 0; i < Dim; ++i)
			ret += data_[i]*data[i];
		return ret;
	}

	value_type length() const
	{
		return std::sqrt(length_quad());
	}

	basic_vector unit() const
	{
		return (*this) * (static_cast<T>(1) / length());
	}

	basic_vector& normalize()
	{
		return *this = unit();
	}

	value_type angle_to(const basic_vector& r) const
	{
		return std::acos(dot(r)/(length()*r.length()));
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
		assert(Dim > 2);
		return (*this)[2];
	}

//	template<typename Dummy>
	const_reference z(/*typename boost::enable_if_c<(Dim > 2), Dummy>* = 0*/) const
	{
		assert(Dim > 2);
		return (*this)[2];
	}

	reference w()
	{
		assert(Dim > 3);
		return (*this)[3];
	}

	const_reference w() const
	{
		assert(Dim > 3);
		return (*this)[3];
	}

/*	template<typename OtherT>
	basic_vector cross(const basic_vector& r, typename boost::enable_if<boost::mpl::and_<boost::is_same<T,OtherT>, boost::mpl::bool_<Dim == 3> > >::type* = 0) const
	{
		return basic_vector(y()*r.z() - z()*r.y(),
		              z()*r.x() - x()*r.z(),
		              x()*r.y() - y()*r.x());
	}*/

	bool is_null() const
	{
		return *this == basic_vector();
	}

	void swap(basic_vector& r)
	{
		std::swap(*this,r);
	}

#define SGE_MATH_VECTOR_SET(z, n, text) void set(BOOST_PP_ENUM_PARAMS(BOOST_PP_ADD(n,1), T const& param)) { BOOST_STATIC_ASSERT(BOOST_PP_ADD(n,1)==Dim); BOOST_PP_REPEAT(BOOST_PP_ADD(n,1), SGE_MATH_VECTOR_CTOR_ASSIGN_N, param) }
BOOST_PP_REPEAT(SGE_MATH_VECTOR_MAX_SIZE, SGE_MATH_VECTOR_SET, void)

	bool nearly_equals(const basic_vector& r, const value_type& radius) const
	{
		const basic_vector tmp(*this - r);
		return dot(tmp,tmp) < radius * radius;
	}

	size_type size() const
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
void place(basic_vector<T,Dim>& v,
           const typename basic_vector<T,Dim>::const_reference radius,
           const typename basic_vector<T,Dim>::const_reference high_angle,
           const typename basic_vector<T,Dim>::const_reference plane_angle,
           typename boost::enable_if_c<Dim==3,T>::type* = 0)
{
	v.x() = radius * std::sin(high_angle) * std::cos(plane_angle);
	v.z() = radius * std::sin(high_angle) * std::sin(plane_angle);
	v.y() = radius * std::cos(high_angle);
}

template<typename T, std::size_t Dim>
void swap(basic_vector<T,Dim>& a, basic_vector<T,Dim>& b)
{
	a.swap(b);
}

template<typename T, std::size_t Dim>
basic_vector<T,Dim> cross(const basic_vector<T,Dim>& l, const basic_vector<T,Dim>& r)
{
	return l.cross(r);
}

template<typename T, std::size_t Dim>
basic_vector<T,Dim> normalize(basic_vector<T,Dim> l)
{
	return l.normalize();
}

template<typename T, std::size_t Dim>
typename basic_vector<T,Dim>::value_type angle_to(const basic_vector<T,Dim>& l, const basic_vector<T,Dim>& r)
{
	return l.angle_to(r);
}

template<typename T, std::size_t Dim>
typename basic_vector<T,Dim>::value_type dot(const basic_vector<T,Dim>& l, const basic_vector<T,Dim>& r)
{
	return l.dot(r);
}

template<typename T, std::size_t Dim>
std::ostream& operator<< (std::ostream& s, const basic_vector<T,Dim>& v)
{
	s << '(';
	for(typename basic_vector<T,Dim>::size_type i = 0; i < Dim-1; ++i)
		s << v[i] << ',';
	s << v[Dim-1] << ')';
	return s;
}

template<typename T, std::size_t Dim>
std::wostream& operator<< (std::wostream& s, const basic_vector<T,Dim>& v)
{
	s << L'(';
	for(typename basic_vector<T,Dim>::size_type i = 0; i < Dim-1; ++i)
		s << v[i] << L',';
	s << v[Dim-1] << L')';
	return s;
}

template<typename T, std::size_t Dim>
std::istream& operator>> (std::istream& s, basic_vector<T,Dim>& v)
{
	char c;
	s >> c;
	if(c != '(')
		s.setstate(std::ios_base::failbit);
	for(typename basic_vector<T,Dim>::size_type i = 0; i < Dim-1; ++i)
	{
		s >> v[i] >> c;
		if(c != ',')
			s.setstate(std::ios_base::failbit);
	}
	s >> v[Dim-1] >> c;
	if(c != ')')
		s.setstate(std::ios_base::failbit);
	return s;
}

template<typename T, std::size_t Dim>
std::wistream& operator>> (std::wistream& s, basic_vector<T,Dim>& v)
{
	wchar_t c;
	s >> c;
	if(c != L'(')
		s.setstate(std::ios_base::failbit);
	for(typename basic_vector<T,Dim>::size_type i = 0; i < Dim-1; ++i)
	{
		s >> v[i] >> c;
		if(c != L',')
			s.setstate(std::ios_base::failbit);
	}
	s >> v[Dim-1] >> c;
	if(c != L')')
		s.setstate(std::ios_base::failbit);
	return s;
}

typedef basic_vector<space_unit,2> vector2;
typedef basic_vector<space_unit,3> vector3;
typedef basic_vector<space_unit,4> vector4;

}
}

#endif
