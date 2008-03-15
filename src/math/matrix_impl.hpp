#ifndef SGE_MATH_MATRIX_IMPL_HPP_INCLUDED
#define SGE_MATH_MATRIX_IMPL_HPP_INCLUDED

#include "matrix.hpp"
#include "compare.hpp"
#include "../algorithm_impl.hpp"
#include "../exception.hpp"
#include <cmath>
#include <algorithm>
#include <functional>

template<typename T, std::size_t N, std::size_t M>
sge::math::basic_matrix<T, N, M>::basic_matrix(no_initialization_tag)
{
}

template<typename T, std::size_t N, std::size_t M>
sge::math::basic_matrix<T, N, M>::basic_matrix(const basic_matrix& r)
{
	copy_n(r.data_, size(), data_);
}

template<typename T, std::size_t N, std::size_t M>
typename sge::math::basic_matrix<T, N, M>&
sge::math::basic_matrix<T, N, M>::operator=(const basic_matrix& r)
{
	copy_n(r.data_, size(), data_);
	return *this;
}

template<typename T, std::size_t N, std::size_t M>
sge::math::basic_matrix<T, N, M>&
sge::math::basic_matrix<T, N, M>::operator+=(const basic_matrix& r)
{
	for(size_type i = 0; i < size(); ++i)
		data_[i] += r.data_[i];
	return *this;
}

template<typename T, std::size_t N, std::size_t M>
sge::math::basic_matrix<T, N, M>&
sge::math::basic_matrix<T, N, M>::operator-=(const basic_matrix& r)
{
	for(size_type i = 0; i < size(); ++i)
		data_[i] -= r.data_[i];
	return *this;
}

template<typename T, std::size_t N, std::size_t M>
sge::math::basic_matrix<T, N, M>&
sge::math::basic_matrix<T, N, M>::operator*=(const value_type& v)
{
	for(size_type i = 0; i < size(); ++i)
		data_[i] *= v;
	return *this;
}

template<typename T, std::size_t N, std::size_t M>
const typename sge::math::basic_matrix<T, N, M>::proxy
sge::math::basic_matrix<T, N, M>::operator[](const size_type j)
{
	return proxy(j,data());
}

template<typename T, std::size_t N, std::size_t M>
const typename sge::math::basic_matrix<T, N, M>::const_proxy
sge::math::basic_matrix<T, N, M>::operator[](const size_type j) const
{
	return const_proxy(j,data());
}

template<typename T, std::size_t N, std::size_t M>
typename sge::math::basic_matrix<T, N, M>::pointer
sge::math::basic_matrix<T, N, M>::data()
{
	return data_;
}

template<typename T, std::size_t N, std::size_t M>
typename sge::math::basic_matrix<T, N, M>::const_pointer
sge::math::basic_matrix<T, N, M>::data() const
{
	return data_;
}

template<typename T, std::size_t N, std::size_t M>
typename sge::math::basic_matrix<T, N, M>::size_type
sge::math::basic_matrix<T, N, M>::size() const
{
	return Dim;
}

template<typename T, std::size_t N, std::size_t M>
inline sge::math::basic_matrix<T,N,M> sge::math::operator+ (const basic_matrix<T,N,M>& r)
{
	basic_matrix<T,N,M> ret;
	for(typename basic_matrix<T,N,M>::size_type i = 0; i < r.size(); ++i)
		ret.data_[i] = +ret.data_[i];
	return ret;
}

template<typename T, std::size_t N, std::size_t M>
inline sge::math::basic_matrix<T,N,M> sge::math::operator- (const basic_matrix<T,N,M>& r)
{
	basic_matrix<T,N,M> ret;
	for(typename basic_matrix<T,N,M>::size_type i = 0; i < r.size(); ++i)
		ret.data_[i] = -ret.data_[i];
	return ret;
}

template<typename T, std::size_t N, std::size_t M>
inline sge::math::basic_matrix<T,N,M> sge::math::operator+ (const basic_matrix<T,N,M>& l, const basic_matrix<T,N,M>& r)
{
	return basic_matrix<T,N,M>(l) += r;
}

template<typename T, std::size_t N, std::size_t M>
inline sge::math::basic_matrix<T,N,M> sge::math::operator- (const basic_matrix<T,N,M>& l, const basic_matrix<T,N,M>& r)
{
	return basic_matrix<T,N,M>(l) -= r;
}

template<typename T, std::size_t N, std::size_t M>
inline sge::math::basic_matrix<T,N,M> sge::math::operator* (const typename basic_matrix<T,N,M>::value_type& l, const basic_matrix<T,N,M>& r)
{
	return basic_matrix<T,N,M>(r) *= l;
}

template<typename T, std::size_t N, std::size_t M1, std::size_t M2>
inline sge::math::basic_matrix<T,N,N> sge::math::operator* (const basic_matrix<T,M1,N>& a, const basic_matrix<T,N,M2>& b)
{
	typedef basic_matrix<T,M1,M2> result_type;
	result_type ret = result_type(no_initialization_tag());
	for(typename basic_matrix<T,M1,N>::size_type i = 0; i < M1; ++i)
		for(typename basic_matrix<T,N,M2>::size_type j = 0; j < M2; ++j)
		{
			typename result_type::value_type v(0);
			for(typename result_type::size_type r = 0; r < N; ++r)
				v += a[i][r] * b[r][j];
			ret[i][j] = v;
		}
	return ret;
}

template<typename T, std::size_t N, std::size_t M>
inline bool sge::math::operator== (const basic_matrix<T,N,M>& l, const basic_matrix<T,N,M>& r)
{
	return std::equal(l.begin(), l.end(), r.begin(), std::ptr_fun(compare<T>));
}

template<typename T, std::size_t N, std::size_t M>
inline bool sge::math::operator!= (const basic_matrix<T,N,M>& l, const basic_matrix<T,N,M>& r)
{
	return !(l==r);
}

template<typename T, std::size_t N, std::size_t M,typename Ch, typename Traits>
inline std::basic_ostream<Ch,Traits>& sge::math::operator<< (std::basic_ostream<Ch,Traits>& s, const basic_matrix<T,N,M>& m)
{
	s << s.widen('(');
	for(typename basic_matrix<T,N,M>::size_type j = 0; j < N; ++j)
	{
		s << s.widen('(');
		for(typename basic_matrix<T,N,M>::size_type i = 0; i < M; ++i)
		{
			s << m[j][i];
			if(i != M-1)
				s << s.widen(',');
		}
		s << s.widen(')');
		if(j != N-1)
			s << s.widen(',');
	}
	return s << s.widen(')');
}

template<typename T, std::size_t N>
inline sge::math::basic_matrix<T,N,N> sge::math::transpose(const basic_matrix<T,N,N>& m)
{
	basic_matrix<T,N,N> ret = basic_matrix<T,N,N>(no_initialization_tag());
	for(typename basic_matrix<T,N,N>::size_type j = 0; j < N; ++j)
		for(typename basic_matrix<T,N,N>::size_type i = 0; i < N; ++i)
			ret[i][j] = m[j][i];
	return ret;
}

inline sge::math::space_matrix sge::math::matrix_translation(const basic_vector<space_unit,3>& v)
{
	return space_matrix
	       (1, 0, 0, v.x(),
	        0, 1, 0, v.y(),
	        0, 0, 1, v.z(),
	        0, 0, 0, 1);

}

inline sge::math::space_matrix sge::math::matrix_translation(const space_unit x, const space_unit y, const space_unit z)
{
	return matrix_translation(math::basic_vector<space_unit,3>(x,y,z));
}

inline sge::math::space_matrix sge::math::matrix_scaling(const basic_vector<space_unit,3>& v)
{
	return space_matrix
	       (v.x(),     0,     0, 0,
	            0, v.y(),     0, 0,
	            0,     0, v.z(), 0,
	            0,     0,     0, 1);
}

inline sge::math::space_matrix sge::math::matrix_scaling(const space_unit x, const space_unit y, const space_unit z)
{
	return matrix_scaling(math::basic_vector<space_unit,3>(x,y,z));
}

#undef near
#undef far

inline sge::math::space_matrix sge::math::matrix_perspective(const space_unit aspect, const space_unit fov, const space_unit near, const space_unit far)
{
	if(compare(far, near))
		throw exception(SGE_TEXT("matrix_perspective(): far may not be near!"));
	if(almost_zero(near))
		throw exception(SGE_TEXT("matrix_perspective(): near must not be 0!"));
	const space_unit h = static_cast<space_unit>(1) / std::tan(fov / static_cast<space_unit>(2)),
	                 w = h / aspect,
	                 q = (far + near) / (far - near);
	return space_matrix
	       (w, 0,                     0, 0,
	        0, h,                     0, 0,
	        0, 0,                     q, 1,
	        0, 0, 2*far*near/(near-far), 0);
}

inline sge::math::space_matrix sge::math::matrix_orthogonal_xy()
{
	return space_matrix
	       (1,0,0,0,
	        0,1,0,0,
	        0,0,0,0,
	        0,0,0,1);
}

inline sge::math::space_matrix sge::math::matrix_rotation_z(const space_unit angle)
{
	const space_unit sinx = std::sin(angle),
	                 cosx = std::cos(angle);
	return space_matrix
	       (cosx, -sinx, 0, 0,
	        sinx,  cosx, 0, 0,
	        0,     0,    1, 0,
	        0,     0,    0, 1);
}

inline sge::math::space_matrix sge::math::matrix_rotation_y(const space_unit angle)
{
	const space_unit sinx = std::sin(angle),
	                 cosx = std::cos(angle);
	return space_matrix
	       (cosx, 0,-sinx, 0,
	        0,  1, 0, 0,
	        sinx,     0,    cosx, 0,
	        0,     0,    0, 1);
}

inline sge::math::space_matrix sge::math::matrix_rotation_x(const space_unit angle)
{
	const space_unit sinx = std::sin(angle),
	                 cosx = std::cos(angle);
	return space_matrix
	       (1,      0,    0, 0,
	        0,  cosx, -sinx, 0,
	        0,  sinx,  cosx, 0,
	        0,     0,     0, 1);
}

inline sge::math::space_matrix sge::math::matrix_identity()
{
	return space_matrix
	       (1,0,0,0,
	        0,1,0,0,
	        0,0,1,0,
	        0,0,0,1);
}

inline sge::math::space_matrix
sge::math::matrix_orthogonal_xy(
	const space_unit left,
	const space_unit right,
	const space_unit top,
	const space_unit bottom,
	const space_unit near,
	const space_unit far)
{
	return space_matrix
	       (2/(right - left), 0, 0, -(right+left)/(right-left),
	        0, 2/(top - bottom), 0, -(top+bottom)/(top-bottom),
	        0, 0, (-2)/(far - near),-(far+near)/(far-near),
	        0, 0, 0, 1);
}

template<typename T, std::size_t N, std::size_t M>
inline sge::math::basic_vector<T,M> sge::math::operator* (const basic_matrix<T,N,M>& m, const basic_vector<T,N>& v)
{
	typedef basic_vector<T,M> result_type;
	result_type ret;
	for(typename result_type::size_type i = 0; i < M; ++i)
		for(typename basic_matrix<T,N,M>::size_type j = 0; j < N; ++j)
			ret[i] += v[j] * m[j][i];
	return ret;
}

#endif
