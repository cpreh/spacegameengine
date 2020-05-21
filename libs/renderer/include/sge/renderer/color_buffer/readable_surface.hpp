//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_COLOR_BUFFER_READABLE_SURFACE_HPP_INCLUDED
#define SGE_RENDERER_COLOR_BUFFER_READABLE_SURFACE_HPP_INCLUDED

#include <sge/image/color/traits/format_fwd.hpp>
#include <sge/image2d/traits/color_tag.hpp>
#include <sge/image2d/traits/dimension.hpp>
#include <sge/renderer/buffer/detail/declare_readable.hpp>
#include <sge/renderer/color_buffer/readable_surface_fwd.hpp>
#include <sge/renderer/color_buffer/surface.hpp>
#include <sge/renderer/color_buffer/tag_from_dimension.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

SGE_RENDERER_BUFFER_DETAIL_DECLARE_READABLE(
	sge::renderer::color_buffer::tag_from_dimension<
		2U
	>
);

FCPPT_PP_POP_WARNING

#endif
