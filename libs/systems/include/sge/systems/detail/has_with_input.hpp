//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_DETAIL_HAS_WITH_INPUT_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_HAS_WITH_INPUT_HPP_INCLUDED

#include <sge/systems/detail/is_with_input.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/algorithms/find.hpp>
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
	typename Choices
>
using
has_with_input
=
brigand::found<
	Choices,
	brigand::bind<
		sge::systems::detail::is_with_input,
		brigand::_1
	>
>;

}
}
}

#endif
