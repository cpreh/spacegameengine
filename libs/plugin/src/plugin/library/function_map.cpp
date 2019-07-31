//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/plugin/library/exception.hpp>
#include <sge/plugin/library/function_map.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::plugin::library::function_map::function_map(
	container &&_functions
)
:
	functions_(
		std::move(
			_functions
		)
	)
{
}

sge::plugin::library::function_base
sge::plugin::library::function_map::function(
	sge::plugin::library::symbol_string const &_name
) const
{
	return
		fcppt::optional::to_exception(
			fcppt::container::find_opt_mapped(
				functions_,
				_name
			),
			[
				&_name
			]{
				return
					sge::plugin::library::exception{
						FCPPT_TEXT("Missing function \"")
						+
						fcppt::from_std_string(
							_name
						)
						+
						FCPPT_TEXT("\" in a library!")
					};
			}
		).get();
}

sge::plugin::library::function_map::container const &
sge::plugin::library::function_map::get() const
{
	return
		functions_;
}
