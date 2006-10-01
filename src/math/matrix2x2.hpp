#ifndef SGE_MATRIX2X2_HPP_INCLUDED
#define SGE_MATRIX2X2_HPP_INCLUDED

#include "./vector2.hpp"
#include "./matrix_proxy.hpp"

namespace sge
{
template<typename T> class matrix2x2 {
public:
	typedef T      value_type;
	typedef std::size_t size_type;
	static const size_type stride = 2;
	typedef detail::matrix_proxy_impl<value_type&, value_type*, stride> proxy;
	typedef detail::matrix_proxy_impl<const value_type&, const value_type*, stride> const_proxy;

	matrix2x2(const value_type& _00, const value_type& _10,
	          const value_type& _01, const value_type& _11)
		: m_00(_00), m_10(_10),
		  m_01(_01), m_11(_11) {}

	proxy operator[](const size_type x) { return proxy(x,&m_00); }
	const_proxy operator[](const size_type x) const { return const_proxy(x,&m_00); }
private:
	value_type m_00, m_10,
	           m_01, m_11;
};

template<typename T> inline vector2<T> operator* (const matrix2x2<T>& l, const vector2<T>& r)
{
	return vector2<T>(l[0][0] * r.x + l[0][1] * r.y,
	                  l[1][0] * r.x + l[1][1] * r.y);
}

}

#endif
