#ifndef SGE_MATH_VECTOR_HPP_INCLUDED
#define SGE_MATH_VECTOR_HPP_INCLUDED

#include <cassert>
#include <cstddef>
#include <ostream>
#include <cmath>
#include <boost/static_assert.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_same.hpp>
#include "../util.hpp"

#ifndef SGE_VECTOR_MAX_SIZE
#define SGE_VECTOR_MAX_SIZE 4
#endif

namespace sge
{
namespace math
{

template<typename T, std::size_t Dim>
class vector {
	BOOST_STATIC_ASSERT(Dim > 1 && Dim <= SGE_VECTOR_MAX_SIZE);
public:
	typedef T           value_type;
	typedef T&          reference;
	typedef const T&    const_reference;
	typedef std::size_t size_type;

#define SGE_MATH_VECTOR_CTOR_ASSIGN_N(z, n, text) (*this)[n] = text##n;
#define SGE_MATH_VECTOR_CTOR(z, n, text) vector(BOOST_PP_ENUM_PARAMS(BOOST_PP_ADD(n,1), T const& param)) { BOOST_STATIC_ASSERT(BOOST_PP_ADD(n,1)==Dim); BOOST_PP_REPEAT(BOOST_PP_ADD(n,1), SGE_MATH_VECTOR_CTOR_ASSIGN_N, param) }
	BOOST_PP_REPEAT(SGE_VECTOR_MAX_SIZE, SGE_MATH_VECTOR_CTOR, void)

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

	vector& normalize()
	{
		const value_type l = length();
		(*this) *= T(1) / l;
		return *this;
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

	//template<typename OtherT>
	reference z(/*typename boost::enable_if<boost::mpl::and_<boost::is_same<T,OtherT>, boost::mpl::bool_<(Dim > 2)> > >::type* = 0*/)
	{
		return (*this)[2];
	}
	
//	template<typename OtherT>
	const_reference z(/*typename boost::enable_if<boost::mpl::and_<boost::is_same<T,OtherT>, boost::mpl::bool_<(Dim > 2)> > >::type* = 0*/) const
	{
		return (*this)[2];
	}

	template<typename OtherT>
	vector cross(const vector& r, typename boost::enable_if<boost::mpl::and_<boost::is_same<T,OtherT>, boost::mpl::bool_<Dim == 3> > >::type* = 0) const
	{
		return vector(y()*r.z() - z()*r.y(),
		              z()*r.x() - x()*r.z(),
			      x()*r.y() - y()*r.x());
	}
private:
	T data[Dim];
};

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
std::ostream& operator << (std::ostream& s, const vector<T,Dim>& v)
{
	s << '(';
	for(typename vector<T,Dim>::size_type i = 0; i < Dim-1; ++i)
		s << v[i] << ',';
	s << v[Dim-1] << ')';
	return s;
}

}
}

#endif
