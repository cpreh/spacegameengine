//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_VERTEX_BUFFER_BASE_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_BUFFER_BASE_HPP_INCLUDED

#include <sge/renderer/buffer/detail/declare_base.hpp>
#include <sge/renderer/buffer/detail/declare_readable.hpp>
#include <sge/renderer/buffer/detail/declare_writable.hpp>
#include <sge/renderer/vertex/buffer_base_fwd.hpp>
#include <sge/renderer/vertex/tag.hpp>
#include <sge/renderer/vertex/traits/color_tag.hpp>
#include <sge/renderer/vertex/traits/const_view_fwd.hpp>
#include <sge/renderer/vertex/traits/dimension.hpp>
#include <sge/renderer/vertex/traits/format_fwd.hpp>
#include <sge/renderer/vertex/traits/view_fwd.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

SGE_RENDERER_BUFFER_DETAIL_DECLARE_BASE(sge::renderer::vertex::tag);

SGE_RENDERER_BUFFER_DETAIL_DECLARE_READABLE(sge::renderer::vertex::tag);

SGE_RENDERER_BUFFER_DETAIL_DECLARE_WRITABLE(sge::renderer::vertex::tag);

FCPPT_PP_POP_WARNING

#endif
