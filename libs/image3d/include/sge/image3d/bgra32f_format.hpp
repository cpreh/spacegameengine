//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE3D_BGRA32F_FORMAT_HPP_INCLUDED
#define SGE_IMAGE3D_BGRA32F_FORMAT_HPP_INCLUDED

#include <sge/image/color/bgra32f_format.hpp>
#include <sge/image/view/basic_format.hpp>


namespace sge::image3d
{

using
bgra32f_format
=
sge::image::view::basic_format<
	3,
	sge::image::color::bgra32f_format
>;

}

#endif
