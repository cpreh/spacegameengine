//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_COLOR_INVALID_CONVERT_HPP_INCLUDED
#define SGE_IMAGE_COLOR_INVALID_CONVERT_HPP_INCLUDED

#include <sge/image/declare_invalid_convert.hpp>
#include <sge/image/invalid_convert.hpp>
#include <sge/image/color/tag.hpp>
#include <sge/image/color/traits/format_fwd.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

namespace sge::image::color
{

using invalid_convert = sge::image::invalid_convert<sge::image::color::tag>;

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

SGE_IMAGE_DECLARE_INVALID_CONVERT(sge::image::color::tag);

FCPPT_PP_POP_WARNING

#endif
