//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_COLOR_HPP_INCLUDED
#define SGE_RENDERER_VF_COLOR_HPP_INCLUDED

#include <sge/renderer/vf/color_base.hpp>
#include <sge/renderer/vf/color_fwd.hpp>
#include <sge/renderer/vf/labels/color.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{

template<
	typename Format
>
struct color
:
sge::renderer::vf::color_base<
	Format
>
{
	typedef
	sge::renderer::vf::labels::color
	label;
};

}
}
}

#endif
