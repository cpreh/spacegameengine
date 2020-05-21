//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_COLOR_BUFFER_CONST_SCOPED_SURFACE_LOCK_HPP_INCLUDED
#define SGE_RENDERER_COLOR_BUFFER_CONST_SCOPED_SURFACE_LOCK_HPP_INCLUDED

#include <sge/image2d/traits/dimension.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/renderer/buffer/detail/declare_const_scoped_lock.hpp>
#include <sge/renderer/color_buffer/const_scoped_surface_lock_fwd.hpp>
#include <sge/renderer/color_buffer/tag_from_dimension.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

SGE_RENDERER_BUFFER_DETAIL_DECLARE_CONST_SCOPED_LOCK(
	sge::renderer::color_buffer::tag_from_dimension<
		2U
	>
);

FCPPT_PP_POP_WARNING

#endif
