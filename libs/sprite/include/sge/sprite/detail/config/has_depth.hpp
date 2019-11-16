//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_CONFIG_HAS_DEPTH_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_CONFIG_HAS_DEPTH_HPP_INCLUDED

#include <sge/sprite/config/with_depth.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal/list/contains.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace config
{

template<
	typename Choices
>
using has_depth
=
metal::contains<
	typename
	Choices::optional_elements,
	sge::sprite::config::with_depth
>;

}
}
}
}

#endif
