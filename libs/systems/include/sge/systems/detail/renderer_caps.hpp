//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_DETAIL_RENDERER_CAPS_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_RENDERER_CAPS_HPP_INCLUDED

#include <sge/systems/detail/is_with_renderer.hpp>
#include <fcppt/metal/index_of_if.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal/lambda/trait.hpp>
#include <metal/list/at.hpp>
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
metal::at<
	Choices,
	fcppt::metal::index_of_if<
		Choices,
		metal::trait<
			sge::systems::detail::is_with_renderer
		>
	>
>::caps;

}
}
}

#endif
