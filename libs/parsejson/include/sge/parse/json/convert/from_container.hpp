//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_JSON_CONVERT_FROM_CONTAINER_HPP_INCLUDED
#define SGE_PARSE_JSON_CONVERT_FROM_CONTAINER_HPP_INCLUDED

#include <sge/parse/json/array.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/make_value.hpp>
#include <sge/parse/json/convert/choose_fundamental.hpp>
#include <fcppt/make_recursive.hpp>
#include <fcppt/algorithm/map.hpp>


namespace sge::parse::json::convert
{

template<
	typename Container
>
sge::parse::json::array
from_container(
	Container const &_container
)
{
	return
		sge::parse::json::array(
			fcppt::algorithm::map<
				sge::parse::json::element_vector
			>(
				_container,
				[](
					typename Container::const_reference _element
				)
				{
					return
						fcppt::make_recursive(
							sge::parse::json::make_value(
								static_cast<
									typename
									sge::parse::json::convert::choose_fundamental<
										typename
										Container::value_type
									>::type
								>(
									_element
								)
							)
						);
				}
			)
		);
}

}

#endif
