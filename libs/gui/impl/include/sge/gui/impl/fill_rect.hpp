//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GUI_IMPL_FILL_RECT_HPP_INCLUDED
#define SGE_GUI_IMPL_FILL_RECT_HPP_INCLUDED

#include <sge/image/color/any/object_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/rucksack/rect_fwd.hpp>


namespace sge
{
namespace gui
{
namespace impl
{

void
fill_rect(
	sge::renderer::device::core &, // NOLINT(google-runtime-references)
	sge::renderer::context::ffp &, // NOLINT(google-runtime-references)
	sge::rucksack::rect const &,
	sge::image::color::any::object const &
);

}
}
}

#endif
