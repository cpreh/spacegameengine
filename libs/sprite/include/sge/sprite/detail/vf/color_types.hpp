//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_VF_COLOR_TYPES_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_VF_COLOR_TYPES_HPP_INCLUDED

#include <sge/sprite/detail/vf/color.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace vf
{

template<
	typename Choices
>
using
color_types
=
metal::list<
	sge::sprite::detail::vf::color<
		Choices
	>
>;

}
}
}
}

#endif
