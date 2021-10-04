//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_COLOR_RGBA32F_FWD_HPP_INCLUDED
#define SGE_IMAGE_COLOR_RGBA32F_FWD_HPP_INCLUDED

#include <sge/image/color/rgba32f_format.hpp>
#include <sge/image/pixel/mizuiro_type_fwd.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace sge::image::color
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wshadow)

using
rgba32f
=
sge::image::pixel::mizuiro_type<
	sge::image::color::rgba32f_format
>;

FCPPT_PP_POP_WARNING

}

#endif
