//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE2D_VIEW_PITCH_HPP_INCLUDED
#define SGE_IMAGE2D_VIEW_PITCH_HPP_INCLUDED

#include <sge/image2d/pitch_fwd.hpp>
#include <sge/image2d/detail/symbol.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/image2d/view/object_fwd.hpp>


namespace sge
{
namespace image2d
{
namespace view
{

SGE_IMAGE2D_DETAIL_SYMBOL
sge::image2d::pitch
pitch(
	sge::image2d::view::object const &
);

SGE_IMAGE2D_DETAIL_SYMBOL
sge::image2d::pitch
pitch(
	sge::image2d::view::const_object const &
);

}
}
}

#endif
