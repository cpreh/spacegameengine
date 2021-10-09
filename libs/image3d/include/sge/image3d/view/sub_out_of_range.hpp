//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE3D_VIEW_SUB_OUT_OF_RANGE_HPP_INCLUDED
#define SGE_IMAGE3D_VIEW_SUB_OUT_OF_RANGE_HPP_INCLUDED

#include <sge/image/view/declare_sub_out_of_range.hpp>
#include <sge/image/view/sub_out_of_range.hpp>
#include <sge/image3d/tag.hpp>
#include <sge/image3d/traits/dimension.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

namespace sge::image3d::view
{

using sub_out_of_range = sge::image::view::sub_out_of_range<sge::image3d::tag>;

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

SGE_IMAGE_VIEW_DECLARE_SUB_OUT_OF_RANGE(sge::image3d::tag);

FCPPT_PP_POP_WARNING

#endif
