//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/font/exception.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/bitmap/impl/load_offset.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/convert/to_int.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/recursive_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/array/from_range.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <fcppt/config/external_end.hpp>


sge::font::vector
sge::font::bitmap::impl::load_offset(
	sge::parse::json::member_map const &_members
)
{
	return
		fcppt::optional::to_exception(
			fcppt::optional::map(
				fcppt::container::array::from_range<
					2
				>(
					sge::parse::json::find_member_exn<
						sge::parse::json::array const
					>(
						fcppt::make_cref(
							_members
						),
						"offset"
					).get().elements
				),
				[](
					std::array<
						fcppt::recursive<
							sge::parse::json::value
						>,
						2
					> const &_elements
				)
				{
					return
						sge::font::vector(
							sge::parse::json::convert::to_int<
								sge::font::unit
							>(
								std::get<
									0
								>(
									_elements
								).get()
							),
							sge::parse::json::convert::to_int<
								sge::font::unit
							>(
								std::get<
									1
								>(
									_elements
								).get()
							)
						);
				}
			),
			[]{
				return
					sge::font::exception{
						FCPPT_TEXT("Bogus offset detected")
					};
			}
		);
}
