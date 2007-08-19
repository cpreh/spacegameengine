#ifndef SGE_MATH_VECTOR_HPP_INCLUDED
#define SGE_MATH_VECTOR_HPP_INCLUDED

#include <cassert>
#include <cstddef>
#include <ostream>
#include <istream>
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
class vector {
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
#define SGE_MATH_VECTOR_CTOR(z, n, text) vector(BOOST_PP_ENUM_PARAMS(BOOST_PP_ADD(n,1), T const& param)) { BOOST_STATIC_ASSERT(BOOST_PP_ADD(n,1)==Dim); BOOST_PP_REPEAT(BOOST_PP_ADD(n,1), SGE_MATH_VECTOR_CTOR_ASSIGN_N, param) }
	BOOST_PP_REPEAT(SGE_MATH_VECTOR_MAX_SIZE, SGE_MATH_VECTOR_CTOR, void)

	vector()
	{
		for(size_type i = 0; i < Dim; ++i)
			data[i] = 0;
	}

	vector(no_initialization_tag)
	{
	}

	template<std::size_t U>
	vector(const vector<T,U>& v, const_reference n = 0, typename boost::enable_if_c<U == Dim-1>::type* =0)
	{
		for(size_type i = 0; i < U; ++i)
			data[i] = v[i];
		data[U] = n;
	}

	vector(const vector& r)
	{
		for(size_type i = 0; i < Dim; ++i)
			data[i] = r[i];
	}

	vector& operator=(const vector& r)
	{
		for(size_type i = 0; i < Dim; ++i)
			data[i] = r[i];
		return *this;
	}

	vector& operator+=(const vector& r)
	{
		for(size_type i = 0; i < Dim; ++i)
			data[i] += r[i];
		return *this;
	}

	vector& operator-=(const vector& r)
	{
		for(size_type i = 0; i < Dim; ++i)
			data[i] -= r[i];
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
		vector ret = vector(no_initialization_tag());
		for(size_type i = 0; i < Dim; ++i)
			ret[i] = +data[i];
		return ret;
	}

	vector operator-() const
	{
		vector ret = vector(no_initialization_tag());
		for(size_type i = 0; i < Dim; ++i)
			ret[i] = -data[i];
		return ret;
	}

	value_type operator*(const vector& r) const
	{
		return dot(r);
	}

	value_type dot(const vector& r) const
	{
		value_type ret(0);
		for(size_type i = 0; i < Dim; ++i)
			ret += (*this)[i] * r[i];
		return ret;
	}

	vector& operator*=(const_reference r)
	{
		for(size_type i = 0; i < Dim; ++i)
			(*this)[i] *= r;
		return *this;
	}

	friend vector operator*(const_reference l, const vector& r)
	{
		return vector(r) *= l;
	}

	friend vector operator*(const vector& l, const_reference r)
	{
		return r * l;
	}

	reference operator[](const size_type pos)
	{
		assert(pos < Dim);
		return data[pos];
	}

	const_reference operator[](const size_type pos) const
	{
		assert(pos < Dim);
		return data[pos];
	}

	reference at(const size_type pos)
	{
		if(pos >= Dim)
			throw exception("vector<T, N>::at(): out of range!");
		return data[pos];
	}

	const_reference at(const size_type pos) const
	{
		if(pos >= Dim)
			throw exception("vector<T, N>::at(): out of range!");
		return data[pos];
	}

	// TODO: do something different for float here
	bool operator==(const vector& r) const
	{
		for(size_type i = 0; i < Dim; ++i)
			if(data[i] != r[i])
				return false;
		return true;
	}

	bool operator!=(const vector& r) const
	{
		return !((*this)==r);
	}

	value_type length_quad() const
	{
		value_type ret(0);
		for(size_type i = 0; i < Dim; ++i)
			ret += data[i]*data[i];
		return ret;
	}

	value_type length() const
	{
		return std::sqrt(length_quad());
	}

	vector unit() const
	{
		return (*this) * (static_cast<T>(1) / length());
	}

	vector& normalize()
	{
		return *this = unit();
	}

	value_type angle_to(const vector& r) const
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
	vector cross(const vector& r, typename boost::enable_if<boost::mpl::and_<boost::is_same<T,OtherT>, boost::mpl::bool_<Dim == 3> > >::type* = 0) const
	{
		return vector(y()*r.z() - z()*r.y(),
		              z()*r.x() - x()*r.z(),
		              x()*r.y() - y()*r.x());
	}*/

	bool is_null() const
	{
		return *this == vector();
	}

	void swap(vector& r)
	{
		std::swap(*this,r);
	}

#define SGE_MATH_VECTOR_SET(z, n, text) void set(BOOST_PP_ENUM_PARAMS(BOOST_PP_ADD(n,1), T const& param)) { BOOST_STATIC_ASSERT(BOOST_PP_ADD(n,1)==Dim); BOOST_PP_REPEAT(BOOST_PP_ADD(n,1), SGE_MATH_VECTOR_CTOR_ASSIGN_N, param) }
BOOST_PP_REPEAT(SGE_MATH_VECTOR_MAX_SIZE, SGE_MATH_VECTOR_SET, void)

	bool nearly_equals(const vector& r, const value_type& radius) const
	{
		const vector tmp(*this - r);
		return dot(tmp,tmp) < radius * radius;
	}

	size_type size() const
	{
		return Dim;
	}

	iterator begin()
	{
		return data;
	}

	iterator end()
	{
		return &data[Dim];
	}

	const_iterator begin() const
	{
		return data;
	}

	const_iterator end() const
	{
		return &data[Dim];
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
private:
	T data[Dim];
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
typename vector<T,Dim>::value_type angle_to(const vector<T,Dim>& l, const vector<T,Dim>& r)
{
	return l.angle_to(r);
}

template<typename T, std::size_t Dim>
typename vector<T,Dim>::value_type dot(const vector<T,Dim>& l, const vector<T,Dim>& r)
{
	return l.dot(r);
}

template<typename T, std::size_t Dim>
std::ostream& operator<< (std::ostream& s, const vector<T,Dim>& v)
{
	s << '(';
	for(typename vector<T,Dim>::size_type i = 0; i < Dim-1; ++i)
		s << v[i] << ',';
	s << v[Dim-1] << ')';
	return s;
}

template<typename T, std::size_t Dim>
std::wostream& operator<< (std::wostream& s, const vector<T,Dim>& v)
{
	s << L'(';
	for(typename vector<T,Dim>::size_type i = 0; i < Dim-1; ++i)
		s << v[i] << L',';
	s << v[Dim-1] << L')';
	return s;
}

template<typename T, std::size_t Dim>
std::istream& operator>> (std::istream& s, vector<T,Dim>& v)
{
	char c;
	s >> c;
	if(c != '(')
		s.setstate(std::ios_base::failbit);
	for(typename vector<T,Dim>::size_type i = 0; i < Dim-1; ++i)
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
std::wistream& operator>> (std::wistream& s, vector<T,Dim>& v)
{
	wchar_t c;
	s >> c;
	if(c != L'(')
		s.setstate(std::ios_base::failbit);
	for(typename vector<T,Dim>::size_type i = 0; i < Dim-1; ++i)
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

typedef vector<space_unit,2> vector2;
typedef vector<space_unit,3> vector3;
typedef vector<space_unit,4> vector4;

}
}

#endif
