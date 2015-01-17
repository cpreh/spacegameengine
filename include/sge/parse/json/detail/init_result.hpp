/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_PARSE_JSON_DETAIL_INIT_RESULT_HPP_INCLUDED
#define SGE_PARSE_JSON_DETAIL_INIT_RESULT_HPP_INCLUDED

#include <fcppt/algorithm/array_init.hpp>
#include <fcppt/math/dim/is_dim.hpp>
#include <fcppt/math/matrix/is_matrix.hpp>
#include <fcppt/math/vector/is_vector.hpp>
#include <fcppt/type_traits/is_std_array.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/or.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace json
{
namespace detail
{

template<
	typename T
>
typename boost::enable_if<
	boost::mpl::or_<
		fcppt::math::matrix::is_matrix<
			T
		>,
		fcppt::math::vector::is_vector<
			T
		>,
		fcppt::math::dim::is_dim<
			T
		>
	>,
	T
>::type
init_result()
{
	return
		T::null();
}

template<
	typename T
>
typename boost::enable_if<
	fcppt::type_traits::is_std_array<
		T
	>,
	T
>::type
init_result()
{
	return
		fcppt::algorithm::array_init<
			T
		>(
			sge::parse::json::detail::init_result<
				typename T::value_type
			>()
		);
}

}
}
}
}

#endif
