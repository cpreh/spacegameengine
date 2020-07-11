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
#include <fcppt/container/join.hpp>
#include <fcppt/type_traits/implication.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <utility>
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
	> &&_init
)
{
	// Check that every subsystem that needs initialization is initialized
	static_assert(
		metal::all_of<
			Choices,
			metal::bind<
				metal::trait<
					fcppt::type_traits::implication
				>,
				metal::trait<
					sge::systems::detail::extract_needs_init
				>,
				metal::bind<
					metal::lambda<
						metal::contains
					>,
					metal::always<
						metal::as_list<
							Inits
						>
					>,
					metal::lambda<
						sge::systems::detail::extract_parameter_type
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
					std::move(
						_init.get()
					),
					[](
						auto &&_element
					)
					{
						return
							sge::systems::detail::make_list_element<
								Choices
							>(
								std::forward<
									decltype(
										_element
									)
								>(
									_element
								)
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
