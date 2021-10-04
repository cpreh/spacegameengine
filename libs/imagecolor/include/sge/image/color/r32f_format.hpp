//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_COLOR_R32F_FORMAT_HPP_INCLUDED
#define SGE_IMAGE_COLOR_R32F_FORMAT_HPP_INCLUDED

#include <sge/image/channel32f.hpp>
#include <sge/image/homogenous_format.hpp>
#include <mizuiro/color/layout/r.hpp>


namespace sge::image::color
{

using
r32f_format
=
sge::image::homogenous_format<
	sge::image::channel32f,
	mizuiro::color::layout::r
>;

}

#endif
