/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_CHRONO_DURATON_ARITHMETIC_HPP_INCLUDED
#define SGE_CHRONO_DURATON_ARITHMETIC_HPP_INCLUDED

namespace sge
{
namespace chrono
{

template<
	typename Rep1,
	typename Period1,
	typename Rep2,
	typename Period2
>
typename common_type<
	duration<
		Rep1,
		Period1
	>,
	duration<
		Rep2,
		Period2
	>
>::type
operator +(
	duration<
		Rep1,
		Period1
	> const &lhs,
	duration<
		Rep2,
		Period2
	> const &rhs
)
{
	return typename common_type<
		duration<
			Rep1,
			Period1
		>,
		duration<
			Rep2,
			Period2
		>
	>::type(
		lhs
	)
	+= rhs;
}

template<
	typename Rep1,
	typename Period1, typename Rep2, typename Period2>
  typename common_type<duration<Rep1, Period1>, duration<Rep2, Period2>>::type
  operator-(const duration<Rep1, Period1>& lhs, const duration<Rep2, Period2>& rhs);
template <typename Rep1, typename Period, typename Rep2>
  duration<typename common_type<Rep1, Rep2>::type, Period>
  operator*(const duration<Rep1, Period>& d, const Rep2& s);
template <typename Rep1, typename Period, typename Rep2>
  duration<typename common_type<Rep1, Rep2>::type, Period>
  operator*(const Rep1& s, const duration<Rep2, Period>& d);
template <typename Rep1, typename Period, typename Rep2>
  duration<typename common_type<Rep1, Rep2>::type, Period>
  operator/(const duration<Rep1, Period>& d, const Rep2& s);
template <typename Rep1, typename Period1, typename Rep2, typename Period2>
  typename common_type<Rep1, Rep2>::type
  operator/(const duration<Rep1, Period1>& lhs, const duration<Rep2, Period2>& rhs);

}
}

#endif
