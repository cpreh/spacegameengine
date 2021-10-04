//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/detail/is_iterable.hpp>
#include <sge/parse/json/detail/is_math_type.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/not.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/reference.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/array/get.hpp>
#include <fcppt/array/init.hpp>
#include <fcppt/array/is_object.hpp>
#include <fcppt/array/object_impl.hpp>
#include <fcppt/array/size.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/math/from_array.hpp>
#include <fcppt/math/to_array_type.hpp>
#include <fcppt/math/matrix/init.hpp>
#include <fcppt/math/matrix/is_matrix.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <string>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge::parse::json
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
	std::enable_if_t<
		std::is_floating_point_v<
			Result
		>
	>
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
					fcppt::make_cref(
						_value
					)
				).get()
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
				fcppt::make_cref(
					_value
				)
			).get();
	}
};

template<
	typename Result
>
struct convert_from_impl<
	Result,
	std::enable_if_t<
		std::is_integral_v<
			Result
		>
		&&
		fcppt::not_(
			std::is_same_v<
				Result,
				bool
			>
		)
	>
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
					fcppt::make_cref(
						_value
					)
				).get()
			);
	}
};

template<
	typename Result
>
struct convert_from_impl<
	Result,
	std::enable_if_t<
		fcppt::math::matrix::is_matrix<
			Result
		>::value
	>
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
				fcppt::make_cref(
					_value
				)
			).get().elements
		);

		using
		outer_size
		=
		typename
		Result::static_rows;

		using
		inner_size
		=
		typename
		Result::static_columns;

		if(
			outer_array.size()
			!=
			outer_size::value
		)
		{
			throw
				sge::parse::exception(
					FCPPT_TEXT("Matrix row count does not match")
				);
		}

		using
		inner_array
		=
		fcppt::array::object<
			fcppt::reference<
				sge::parse::json::element_vector const
			>,
			outer_size::value
		>;

		auto const inner(
			fcppt::array::init<
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
							fcppt::make_cref(
								outer_array[
									_index
								].get()
							)
						).get().elements
					);

					if(
						result.size()
						!=
						inner_size::value
					)
					{
						throw
							sge::parse::exception(
								FCPPT_TEXT("Matrix column count does not match")
							);
					}

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
							fcppt::array::get<
								_index.row()
							>(
								inner
							).get()[
								_index.column()
							].get()
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
	std::enable_if_t<
		sge::parse::json::detail::is_iterable<
			Result
		>::value
		&&
		fcppt::not_(
			fcppt::array::is_object<
				Result
			>::value
		)
		&&
		fcppt::not_(
			std::is_same_v<
				Result,
				std::string
			>
		)
	>
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
					fcppt::make_ref(
						_value
					)
				).get().elements,
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
	std::enable_if_t<
		fcppt::array::is_object<
			Result
		>::value
	>
>
{
	static
	Result
	execute(
		sge::parse::json::value const &_value
	)
	{
		auto const &array(
			sge::parse::json::get_exn<
				sge::parse::json::array
			>(
				fcppt::make_cref(
					_value
				)
			).get()
		);

		if(
			fcppt::array::size<
				Result
			>::value
			!=
			array.elements.size()
		)
		{
			throw
				sge::parse::exception(
					FCPPT_TEXT("Tried to convert into an array, but the dimensions did not match. Target array has dimension ")
					+
					fcppt::output_to_fcppt_string(
						fcppt::array::size<
							Result
						>::value
					)
					+
					FCPPT_TEXT(", source array has dimension ")
					+
					fcppt::output_to_fcppt_string(
						array.elements.size()
					)
				);
		}

		return
			fcppt::array::init<
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
							].get()
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
	std::enable_if_t<
		sge::parse::json::detail::is_math_type<
			Result
		>::value
	>
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
	sge::parse::json::value
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
	std::enable_if_t<
		std::is_same_v<
			sge::parse::json::object,
			Result
		>
		||
		std::is_same_v<
			sge::parse::json::array,
			Result
		>
		||
		std::is_same_v<
			std::string,
			Result
		>
	>
>
{
	static
	Result
	execute(
		sge::parse::json::value const &_value
	)
	{
		return
			sge::parse::json::get_exn<
				Result
			>(
				fcppt::make_cref(
					_value
				)
			).get();
	}
};

}

#endif
