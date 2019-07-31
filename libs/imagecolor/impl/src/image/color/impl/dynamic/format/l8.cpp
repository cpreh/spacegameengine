//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/color/format.hpp>
#include <sge/image/color/impl/dynamic/format/l8.hpp>
#include <sge/image/color/impl/dynamic/format/luminance_c8_1.hpp>
#include <sge/image/color/impl/dynamic/format/object_impl.hpp>
#include <mizuiro/color/layout/l.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)
FCPPT_PP_DISABLE_CLANG_WARNING(-Wexit-time-destructors)

sge::image::color::impl::dynamic::format::luminance_c8_1 const
sge::image::color::impl::dynamic::format::l8{
	mizuiro::color::layout::l{},
	sge::image::color::format::l8
};

FCPPT_PP_POP_WARNING
