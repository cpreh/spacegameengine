//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_COLOR_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_COLOR_HPP_INCLUDED

#include <sge/image/color/format_from_static.hpp>
#include <sge/renderer/vf/dynamic/color.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{
namespace detail
{

template<
	typename Format
>
sge::renderer::vf::dynamic::color
make_color()
{
	return
		sge::renderer::vf::dynamic::color(
			sge::image::color::format_from_static<
				Format
			>()
		);
}

}
}
}
}
}

#endif
