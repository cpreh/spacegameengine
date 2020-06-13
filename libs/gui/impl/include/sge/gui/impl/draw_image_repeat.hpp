//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GUI_IMPL_DRAW_IMAGE_REPEAT_HPP_INCLUDED
#define SGE_GUI_IMPL_DRAW_IMAGE_REPEAT_HPP_INCLUDED

#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/rucksack/rect_fwd.hpp>
#include <sge/texture/part_fwd.hpp>


namespace sge
{
namespace gui
{
namespace impl
{

void
draw_image_repeat(
	sge::renderer::device::core &,
	sge::renderer::context::ffp &,
	sge::texture::part const &,
	sge::rucksack::rect
);

}
}
}

#endif
