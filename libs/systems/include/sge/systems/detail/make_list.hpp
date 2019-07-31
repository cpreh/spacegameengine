//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_DETAIL_MAKE_LIST_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_MAKE_LIST_HPP_INCLUDED

#include <sge/systems/list_impl.hpp>
#include <sge/systems/detail/any_list.hpp>
#include <sge/systems/detail/extract_needs_init.hpp>
#include <sge/systems/detail/extract_parameter_type.hpp>
#include <sge/systems/detail/list.hpp>
#include <sge/systems/detail/make_defaults.hpp>
#include <sge/systems/detail/make_list_element.hpp>
#include <fcppt/algorithm/loop_break_tuple.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/brigand/all_of.hpp>
#include <fcppt/brigand/found_t.hpp>
#include <fcppt/brigand/implication.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/functions/lambda/apply.hpp>
#include <brigand/functions/lambda/bind.hpp>
#include <brigand/types/args.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace systems
{
namespace detail
{

template<
	typename Choices,
	typename Inits
>
sge::systems::detail::list
make_list(
	sge::systems::list<
		Inits
	> const &_init
)
{
	// Check that every subsystem that needs initialization is initialized
	static_assert(
		fcppt::brigand::all_of<
			Choices,
			brigand::bind<
				fcppt::brigand::implication,
				brigand::bind<
					sge::systems::detail::extract_needs_init,
					brigand::_1
				>,
				brigand::bind<
					fcppt::brigand::found_t,
					brigand::pin<
						Inits
					>,
					brigand::bind<
						sge::systems::detail::extract_parameter_type,
						brigand::_1
					>
				>
			>
		>::value,
		"A subsystem has not been initialized"
	);

	return
		sge::systems::detail::list{
			fcppt::container::join(
				// Initialize every subsystem given in the parameters
				fcppt::algorithm::map<
					sge::systems::detail::any_list
				>(
					_init.get(),
					[](
						auto const &_element
					)
					{
						return
							sge::systems::detail::make_list_element<
								Choices
							>(
								_element
							);
					}
				),
				// For every subsystem that doesn't need initialization and is not
				// initialized, add a default parameter
				sge::systems::detail::make_defaults<
					Choices,
					Inits
				>()
			)
		};
}

}
}
}

#endif
