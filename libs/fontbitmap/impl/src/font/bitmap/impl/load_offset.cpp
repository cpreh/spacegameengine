//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/font/exception.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/bitmap/impl/load_offset.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/convert/to_int.hpp>
#include <fcppt/text.hpp>


sge::font::vector
sge::font::bitmap::impl::load_offset(
	sge::parse::json::member_map const &_members
)
{
	sge::parse::json::element_vector const &elements(
		sge::parse::json::find_member_exn<
			sge::parse::json::array const
		>(
			_members,
			"offset"
		).elements
	);

	// TODO: at_optional
	if(
		elements.size() != 2
	)
		throw
			sge::font::exception{
				FCPPT_TEXT("Bogus offset detected")
			};

	return
		sge::font::vector(
			sge::parse::json::convert::to_int<
				sge::font::unit
			>(
				elements[0].get()
			),
			sge::parse::json::convert::to_int<
				sge::font::unit
			>(
				elements[1].get()
			)
		);
}
