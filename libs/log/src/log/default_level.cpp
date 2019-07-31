//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/log/default_level.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/optional_level.hpp>


fcppt::log::optional_level
sge::log::default_level()
{
	return
		fcppt::log::optional_level{
			fcppt::log::level::info
		};
}
