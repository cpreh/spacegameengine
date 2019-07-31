//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/systems/empty_list.hpp>
#include <sge/systems/make_empty_list.hpp>
#include <fcppt/config/external_begin.hpp>
#include <tuple>
#include <fcppt/config/external_end.hpp>


sge::systems::empty_list
sge::systems::make_empty_list()
{
	return
		sge::systems::empty_list{
			std::tuple<>{}
		};
}
