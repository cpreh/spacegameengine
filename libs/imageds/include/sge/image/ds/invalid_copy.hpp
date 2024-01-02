//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_DS_INVALID_COPY_HPP_INCLUDED
#define SGE_IMAGE_DS_INVALID_COPY_HPP_INCLUDED

#include <sge/image/declare_invalid_copy.hpp>
#include <sge/image/invalid_copy.hpp>
#include <sge/image/ds/tag.hpp>
#include <sge/image/ds/traits/format_fwd.hpp> // IWYU pragma: keep
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

namespace sge::image::ds
{

using invalid_copy = sge::image::invalid_copy<sge::image::ds::tag>;

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

SGE_IMAGE_DECLARE_INVALID_COPY(sge::image::ds::tag);

FCPPT_PP_POP_WARNING

#endif
