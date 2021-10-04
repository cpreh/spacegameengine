//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_COLOR_A8_FORMAT_HPP_INCLUDED
#define SGE_IMAGE_COLOR_A8_FORMAT_HPP_INCLUDED

#include <sge/image/channel8.hpp>
#include <sge/image/homogenous_format.hpp>
#include <mizuiro/color/layout/alpha.hpp>


namespace sge::image::color
{

using
a8_format
=
sge::image::homogenous_format<
	sge::image::channel8,
	mizuiro::color::layout::alpha
>;

}

#endif
