//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_DS_LAYOUT_DEPTH_HPP_INCLUDED
#define SGE_IMAGE_DS_LAYOUT_DEPTH_HPP_INCLUDED

#include <sge/image/ds/channel/depth.hpp>
#include <sge/image/ds/space/depth.hpp>
#include <mizuiro/color/layout/make.hpp>
#include <fcppt/mpl/list/object.hpp>

namespace sge::image::ds::layout
{

using depth = mizuiro::color::layout::
    make<sge::image::ds::space::depth, fcppt::mpl::list::object<sge::image::ds::channel::depth>>;

}

#endif
