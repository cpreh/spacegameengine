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
#include <fcppt/algorithm/loop_break_brigand.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/brigand/found_t.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/algorithms/remove.hpp>
#include <brigand/functions/lambda/apply.hpp>
#include <brigand/functions/lambda/bind.hpp>
#include <brigand/functions/logical/or.hpp>
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
sge::systems::detail::any_list
make_defaults()
{
	return
		fcppt::algorithm::map<
			sge::systems::detail::any_list
		>(
			brigand::remove_if<
				Choices,
				brigand::bind<
					brigand::or_,
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
