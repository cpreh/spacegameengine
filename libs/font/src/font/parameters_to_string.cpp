//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/font/parameters.hpp>
#include <sge/font/parameters_to_string.hpp>
#include <sge/font/ttf_size.hpp>
#include <sge/font/weight/unit.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/maybe.hpp>


fcppt::string
sge::font::parameters_to_string(
	sge::font::parameters const &_parameters
)
{
	auto const default_function(
		[]{
			return
				fcppt::string{
					FCPPT_TEXT("default")
				};
		}
	);

	return
		FCPPT_TEXT("( ")
		FCPPT_TEXT("ttf_size: ")
		+
		fcppt::optional::maybe(
			_parameters.ttf_size(),
			default_function,
			[](
				sge::font::ttf_size const _ttf_size
			)
			{
				return
					fcppt::output_to_fcppt_string(
						_ttf_size
					);
			}
		)
		+
		FCPPT_TEXT(", ")
		FCPPT_TEXT("family: ")
		+
		fcppt::optional::from(
			_parameters.family(),
			default_function
		)
		+
		FCPPT_TEXT(", ")
		FCPPT_TEXT("weight: ")
		+
		fcppt::optional::maybe(
			_parameters.weight(),
			default_function,
			[](
				sge::font::weight::unit const _weight
			)
			{
				return
					fcppt::output_to_fcppt_string(
						_weight
					);
			}
		)
		+
		FCPPT_TEXT(", ")
		FCPPT_TEXT("italic: ")
		+
		fcppt::output_to_fcppt_string(
			_parameters.italic()
		)
		+
		FCPPT_TEXT(" )");
}
