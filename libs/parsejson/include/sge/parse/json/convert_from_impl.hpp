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


#ifndef SGE_PARSE_JSON_CONVERT_FROM_IMPL_HPP_INCLUDED
#define SGE_PARSE_JSON_CONVERT_FROM_IMPL_HPP_INCLUDED

#include <sge/parse/exception.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/convert_from_fwd.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/float_type.hpp>
#include <sge/parse/json/get_exn.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/string.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/detail/is_math_type.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/reference.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/array_init.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/container/array_size.hpp>
#include <fcppt/math/from_array.hpp>
#include <fcppt/math/to_array_type.hpp>
#include <fcppt/math/matrix/init.hpp>
#include <fcppt/math/matrix/is_matrix.hpp>
#include <fcppt/type_traits/is_iterable.hpp>
#include <fcppt/type_traits/is_std_array.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/utility/enable_if.hpp>
#include <cstddef>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace json
{

template<
	typename Result,
	typename Enable = void
>
struct convert_from_impl;

template<
	typename Result
>
struct convert_from_impl<
	Result,
	typename
	boost::enable_if<
		std::is_floating_point<
			Result
		>
	>::type
>
{
	static
	Result
	execute(
		sge::parse::json::value const &_value
	)
	{
		return
			fcppt::cast::size<
				Result
			>(
				sge::parse::json::get_exn<
					sge::parse::json::float_type
				>(
					_value
				)
			);
	}
};

template<>
struct convert_from_impl<
	bool
>
{
	static
	bool
	execute(
		sge::parse::json::value const &_value
	)
	{
		return
			sge::parse::json::get_exn<
				bool const
			>(
				_value
			);
	}
};

template<
	typename Result
>
struct convert_from_impl<
	Result,
	typename
	boost::enable_if<
		boost::mpl::and_<
			std::is_integral<
				Result
			>,
			boost::mpl::not_<
				std::is_same<
					Result,
					bool
				>
			>
		>
	>::type
>
{
	static
	Result
	execute(
		sge::parse::json::value const &_value
	)
	{
		return
			static_cast<
				Result
			>(
				sge::parse::json::get_exn<
					sge::parse::json::int_type
				>(
					_value
				)
			);
	}
};

template<
	typename Result
>
struct convert_from_impl<
	Result,
	typename
	boost::enable_if<
		fcppt::math::matrix::is_matrix<
			Result
		>
	>::type
>
{
	static
	Result
	execute(
		sge::parse::json::value const &_value
	)
	{
		sge::parse::json::element_vector const &outer_array(
			sge::parse::json::get_exn<
				sge::parse::json::array
			>(
				_value
			).elements
		);

		typedef
		typename
		Result::static_rows
		outer_size;

		typedef
		typename
		Result::static_columns
		inner_size;

		if(
			outer_array.size()
			!=
			outer_size::value
		)
			throw
				sge::parse::exception(
					FCPPT_TEXT("Matrix row count does not match")
				);

		typedef
		std::array<
			fcppt::reference<
				sge::parse::json::element_vector const
			>,
			outer_size::value
		>
		inner_array;

		inner_array const inner(
			fcppt::algorithm::array_init<
				inner_array
			>(
				[
					&outer_array
				](
					auto const _index
				)
				{
					sge::parse::json::element_vector const &result(
						sge::parse::json::get_exn<
							sge::parse::json::array
						>(
							outer_array[
								_index
							]
						).elements
					);

					if(
						result.size()
						!=
						inner_size::value
					)
						throw
							sge::parse::exception(
								FCPPT_TEXT("Matrix column count does not match")
							);

					return
						fcppt::make_cref(
							result
						);
				}
			)
		);

		return
			fcppt::math::matrix::init<
				Result
			>(
				[
					&inner
				](
					auto const _index
				)
				{
					return
						sge::parse::json::convert_from<
							typename
							Result::value_type
						>(
							std::get<
								_index.row
							>(
								inner
							).get()[
								_index.column
							]
						);
				}
			);
	}
};


// Assume array_type (exception string)
// To be convertible, the type T needs to:
// - have begin/end
// - have value_type
// - have insert(iterator,value)
template<
	typename Result
>
struct convert_from_impl<
	Result,
	typename
	boost::enable_if<
		boost::mpl::and_<
			fcppt::type_traits::is_iterable<
				Result
			>,
			boost::mpl::not_<
				fcppt::type_traits::is_std_array<
					Result
				>
			>,
			boost::mpl::not_<
				std::is_same<
					Result,
					sge::parse::json::string
				>
			>
		>
	>::type
>
{
	static
	Result
	execute(
		sge::parse::json::value const &_value
	)
	{
		return
			fcppt::algorithm::map<
				Result
			>(
				sge::parse::json::get_exn<
					sge::parse::json::array
				>(
					_value
				).elements,
				[](
					sge::parse::json::value const &_inner
				)
				{
					return
						sge::parse::json::convert_from<
							typename
							Result::value_type
						>(
							_inner
						);
				}
			);
	}
};

template<
	typename Result
>
struct convert_from_impl<
	Result,
	typename
	boost::enable_if<
		fcppt::type_traits::is_std_array<
			Result
		>
	>::type
>
{
	static
	Result
	execute(
		sge::parse::json::value const &_value
	)
	{
		sge::parse::json::array const &array(
			sge::parse::json::get_exn<
				sge::parse::json::array
			>(
				_value
			)
		);

		if(
			fcppt::container::array_size<
				Result
			>::value
			!=
			array.elements.size()
		)
			throw
				sge::parse::exception(
					FCPPT_TEXT("Tried to convert into an array, but the dimensions did not match. Target array has dimension ")
					+
					fcppt::insert_to_fcppt_string(
						fcppt::container::array_size<
							Result
						>::value
					)
					+
					FCPPT_TEXT(", source array has dimension ")
					+
					fcppt::insert_to_fcppt_string(
						array.elements.size()
					)
				);

		return
			fcppt::algorithm::array_init<
				Result
			>(
				[
					&array
				](
					auto const _index
				)
				{
					return
						sge::parse::json::convert_from<
							typename
							Result::value_type
						>(
							array.elements[
								_index()
							]
						);
				}
			);
	}
};

template<
	typename Result
>
struct convert_from_impl<
	Result,
	typename
	boost::enable_if<
		sge::parse::json::detail::is_math_type<
			Result
		>
	>::type
>
{
	static
	Result
	execute(
		sge::parse::json::value const &_value
	)
	{
		return
			fcppt::math::from_array<
				Result
			>(
				sge::parse::json::convert_from<
					fcppt::math::to_array_type<
						Result
					>
				>(
					_value
				)
			);
	}
};

// Assume...nothing. You cannot json::get for a json::value, hence
// this special case
template<>
struct convert_from_impl<
	sge::parse::json::value
>
{
	static
	sge::parse::json::value const &
	execute(
		sge::parse::json::value const &_value
	)
	{
		return
			_value;
	}
};

// Everything else -> has to be a json type!
template<
	typename Result
>
struct convert_from_impl<
	Result,
	typename
	boost::enable_if<
		boost::mpl::or_<
			std::is_same<
				sge::parse::json::object,
				Result
			>,
			std::is_same<
				sge::parse::json::array,
				Result
			>,
			std::is_same<
				sge::parse::json::string,
				Result
			>
		>
	>::type
>
{
	static
	Result const &
	execute(
		sge::parse::json::value const &_value
	)
	{
		return
			sge::parse::json::get_exn<
				Result
			>(
				_value
			);
	}
};

}
}
}

#endif
