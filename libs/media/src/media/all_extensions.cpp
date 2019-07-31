//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/media/all_extensions.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wexit-time-destructors)
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

sge::media::optional_extension_set const
sge::media::all_extensions{};

FCPPT_PP_POP_WARNING
