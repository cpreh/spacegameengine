//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_VF_COLOR_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_VF_COLOR_HPP_INCLUDED

#include <sge/renderer/vf/color.hpp>
#include <sge/sprite/detail/config/color_format.hpp>


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
struct color
{
	typedef sge::renderer::vf::color<
		typename sge::sprite::detail::config::color_format<
			Choices
		>::type
	> type;
};

}
}
}
}

#endif
