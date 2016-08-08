/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_PARSE_IMPL_RESULT_WITH_VALUE_IMPL_HPP_INCLUDED
#define SGE_PARSE_IMPL_RESULT_WITH_VALUE_IMPL_HPP_INCLUDED

#include <sge/parse/result.hpp>
#include <sge/parse/result_with_value.hpp>


template<
	typename Start
>
sge::parse::result_with_value<
	Start
>::result_with_value(
	optional_start const &_start,
	sge::parse::result const &_result
)
:
	start_(
		_start
	),
	result_(
		_result
	)
{
}

template<
	typename Start
>
typename
sge::parse::result_with_value<
	Start
>::optional_start const &
sge::parse::result_with_value<
	Start
>::start() const
{
	return
		start_;
}

template<
	typename Start
>
sge::parse::result const &
sge::parse::result_with_value<
	Start
>::result() const
{
	return
		result_;
}

#endif
