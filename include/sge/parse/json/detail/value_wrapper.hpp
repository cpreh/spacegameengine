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


#ifndef SGE_PARSE_JSON_DETAIL_VALUE_WRAPPER_HPP_INCLUDED
#define SGE_PARSE_JSON_DETAIL_VALUE_WRAPPER_HPP_INCLUDED

#include <sge/parse/json/value.hpp>
#include <sge/parse/json/detail/value_wrapper_fwd.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/assert/optional_error.hpp>


namespace sge
{
namespace parse
{
namespace json
{
namespace detail
{

class value_wrapper
{
public:
	value_wrapper()
	:
		value_()
	{
	}

	template<
		typename T
	>
	value_wrapper(
		T const &_arg
	)
	:
		value_(
			sge::parse::json::value(
				_arg
			)
		)
	{
	}

	sge::parse::json::value const &
	get() const
	{
		return
			FCPPT_ASSERT_OPTIONAL_ERROR(
				value_
			);
	}
private:
	typedef
	fcppt::optional::object<
		json::value
	>
	optional_value;

	optional_value value_;
};

}
}
}
}

#endif
