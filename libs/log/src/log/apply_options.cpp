//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/log/apply_options.hpp>
#include <sge/log/option.hpp>
#include <sge/log/option_container.hpp>
#include <fcppt/log/context.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/log/optional_level.hpp>


void
sge::log::apply_options(
	fcppt::log::context_reference const _context,
	sge::log::option_container const &_options
)
{
	for(
		sge::log::option const &option
		:
		_options
	)
		_context.get().set(
			option.location(),
			fcppt::log::optional_level{
				option.level()
			}
		);
}
