//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_DEPTH_STENCIL_BUFFER_SURFACE_HPP_INCLUDED
#define SGE_RENDERER_DEPTH_STENCIL_BUFFER_SURFACE_HPP_INCLUDED

#include <sge/image/ds/traits/format_fwd.hpp> // IWYU pragma: keep
#include <sge/imageds2d/tag.hpp>
#include <sge/imageds2d/traits/color_tag.hpp> // IWYU pragma: keep
#include <sge/imageds2d/traits/dimension.hpp> // IWYU pragma: keep
#include <sge/renderer/buffer/detail/declare_base.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_fwd.hpp> // IWYU pragma: export
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

SGE_RENDERER_BUFFER_DETAIL_DECLARE_BASE(sge::imageds2d::tag);

FCPPT_PP_POP_WARNING

#endif
