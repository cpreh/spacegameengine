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


#ifndef SGE_CHRONO_COMMON_TYPE_HPP_INCLUDED
#define SGE_CHRONO_COMMON_TYPE_HPP_INCLUDED

#include <sge/chrono/time_point_fwd.hpp>
#include <sge/chrono/duration_fwd.hpp>
#include <sge/type_traits/common_type.hpp>
#include <sge/ratio.hpp>

namespace sge
{
namespace chrono
{

template<
	typename T1,
	typename T2
>
struct common_type;

template<
	typename Rep1,
	typename Period1,
	typename Rep2,
	typename Period2
>
struct common_type<
	chrono::duration<
		Rep1,
		Period1
	>,
	chrono::duration<
		Rep2,
		Period2
	>
>
{
	typedef chrono::duration<
		typename type_traits::common_type<
			Rep1,
			Rep2
		>::type,
		typename detail::ratio_gcd<
			Period1,
			Period2
		>::type
	> type;
};

template<
	typename Clock,
	typename Duration1,
	typename Duration2
>
struct common_type<
	chrono::time_point<
		Clock,
		Duration1
	>,
	chrono::time_point<
		Clock,
		Duration2
	>
>
{
	typedef chrono::time_point<
		Clock,
		typename type_traits::common_type<
			Duration1,
			Duration2
		>::type
	> type;
};

}
}

#endif
