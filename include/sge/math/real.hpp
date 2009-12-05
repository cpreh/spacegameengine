#ifndef SGE_MATH_REAL_HPP_INCLUDED
#define SGE_MATH_REAL_HPP_INCLUDED

#include <sge/sn_cast.hpp>
#include <ostream>
#include <istream>
#include <cmath>

#define SGE_MATH_REAL_FORWARD_COMPARISON_OPERATOR(op) bool operator op(real const &_t) const { return t_ op _t.t_; }
#define SGE_MATH_REAL_FORWARD_ASSIGNMENT_OPERATOR(op) real &operator op(real const &_t) { t_ op _t.t_; return *this; }
#define SGE_MATH_REAL_FORWARD_BINARY_OPERATOR(op) real operator op(real const &_t) const { return real(t_ op _t.t_); }

namespace sge
{
namespace math
{
template
<
	typename T,
	typename Epsilon
>
class real
{
public:
	typedef T value_type;

	explicit
	real() {}

	template<typename U>
	explicit 
	real(
		U const _t) 
	:
		t_(
			sge::sn_cast<T>(
				_t))
	{}
	
	value_type value() const { return t_; }

	SGE_MATH_REAL_FORWARD_ASSIGNMENT_OPERATOR(+=)
	SGE_MATH_REAL_FORWARD_ASSIGNMENT_OPERATOR(-=)
	SGE_MATH_REAL_FORWARD_ASSIGNMENT_OPERATOR(*=)
	SGE_MATH_REAL_FORWARD_ASSIGNMENT_OPERATOR(/=)

	SGE_MATH_REAL_FORWARD_COMPARISON_OPERATOR(<)
	SGE_MATH_REAL_FORWARD_COMPARISON_OPERATOR(<=)
	SGE_MATH_REAL_FORWARD_COMPARISON_OPERATOR(>)
	SGE_MATH_REAL_FORWARD_COMPARISON_OPERATOR(>=)

	SGE_MATH_REAL_FORWARD_BINARY_OPERATOR(+)
	SGE_MATH_REAL_FORWARD_BINARY_OPERATOR(-)
	SGE_MATH_REAL_FORWARD_BINARY_OPERATOR(*)
	SGE_MATH_REAL_FORWARD_BINARY_OPERATOR(/)

	real operator%(real const &_t) { return real(std::fmod(t_,_t.t_)); }
	real &operator%=(real const &_t) { t_ = *this % _t; return *this; }

	bool operator==(real const &_t) const { return std::fabs(_t.t_ - t_) < Epsilon::value(); }
	bool operator!=(real const &_t) const { return !(*this == _t); }
	real const operator-() const { return real(-t_); }
	real const operator+() const { return *this; }
private:
	T t_;
};

template
<
	typename T,
	typename U
>
T const real_cast(
	U const u)
{
	return T(
		static_cast<typename T::value_type>(
			u));
}
}
}

template<
	typename T,
	typename U,
	typename Ch,
	typename Traits
>
inline std::basic_ostream<Ch, Traits> &
operator<<(
	std::basic_ostream<Ch, Traits> &s,
	sge::math::real<T,U> const &v)
{
	return s << v.value();
}

template<
	typename T,
	typename U,
	typename Ch,
	typename Traits
>
inline std::basic_istream<Ch, Traits> &
operator>>(
	std::basic_istream<Ch, Traits> &s,
	sge::math::real<T,U> &v)
{
	T value;
	s >> value;
	return 
		sge::math::real<T,U>(
			value);
}

#endif
