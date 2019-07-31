//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_DETAIL_RENDERER_CAPS_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_RENDERER_CAPS_HPP_INCLUDED

#include <sge/systems/detail/is_with_renderer.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/algorithms/find.hpp>
#include <brigand/functions/lambda/bind.hpp>
#include <brigand/sequences/front.hpp>
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
renderer_caps
=
typename
brigand::front<
	brigand::find<
		Choices,
		brigand::bind<
			sge::systems::detail::is_with_renderer,
			brigand::_1
		>
	>
>::caps;

}
}
}

#endif
