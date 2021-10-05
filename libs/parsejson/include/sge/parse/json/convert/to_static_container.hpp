//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_JSON_CONVERT_TO_STATIC_CONTAINER_HPP_INCLUDED
#define SGE_PARSE_JSON_CONVERT_TO_STATIC_CONTAINER_HPP_INCLUDED

#include <sge/parse/exception.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/get_exn.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/convert/choose_fundamental.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/text.hpp>


namespace sge::parse::json::convert
{

template<
	typename Container
>
Container
to_static_container(
	sge::parse::json::array const &_array
)
{
	// TODO(philipp): array::from_container
	if(
		_array.elements.size()
		!=
		static_cast<
			sge::parse::json::element_vector::size_type
		>(
			Container::dim_wrapper::value
		)
	)
	{
		throw sge::parse::exception(
			FCPPT_TEXT("convert::to_static_container: unequal amount of elements!")
		);
	}

	Container result{
		fcppt::no_init()
	};

	for(
		sge::parse::json::element_vector::size_type const index
		:
		fcppt::make_int_range_count(
			_array.elements.size()
		)
	)
	{
		result.get_unsafe(
			static_cast<
				typename
				Container::size_type
			>(
				index
			)
		) =
			static_cast<
				typename Container::value_type
			>(
				sge::parse::json::get_exn<
					typename
					sge::parse::json::convert::choose_fundamental<
						typename
						Container::value_type
					>::type
				>(
					fcppt::make_cref(
						_array.elements[
							index
						].get()
					)
				).get()
			);
	}

	return
		result;
}

}

#endif
