//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/plugin/name.hpp>
#include <sge/systems/font.hpp>
#include <sge/systems/optional_name.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::systems::font::font()
:
	name_()
{
}

sge::systems::font &
sge::systems::font::name(
	sge::plugin::name &&_name
)
{
	name_ =
		sge::systems::optional_name(
			std::move(
				_name
			)
		);

	return
		*this;
}

sge::systems::optional_name const &
sge::systems::font::name() const
{
	return
		name_;
}
