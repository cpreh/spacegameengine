//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_DETAIL_MAKE_DEFAULTS_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_MAKE_DEFAULTS_HPP_INCLUDED

#include <sge/systems/detail/any_list.hpp>
#include <sge/systems/detail/extract_needs_init.hpp>
#include <sge/systems/detail/extract_parameter_type.hpp>
#include <sge/systems/detail/make_default_element.hpp>
#include <fcppt/algorithm/loop_break_metal.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
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
sge::systems::detail::any_list
make_defaults()
{
	return
		fcppt::algorithm::map<
			sge::systems::detail::any_list
		>(
			metal::remove_if<
				Choices,
				metal::bind<
					metal::lambda<
						metal::or_
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
			>{},
			[](
				auto const _type
			)
			{
				return
					sge::systems::detail::make_default_element(
						_type
					);
			}
		);
}

}
}
}

#endif
