//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/color/format.hpp>
#include <sge/image/color/impl/dynamic/format/object_impl.hpp>
#include <sge/image/color/impl/dynamic/format/rgb_c8_4.hpp>
#include <sge/image/color/impl/dynamic/format/rgbx8.hpp>
#include <mizuiro/color/layout/rgbx.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)
FCPPT_PP_DISABLE_CLANG_WARNING(-Wexit-time-destructors)

// NOLINTNEXTLINE(fuchsia-statically-constructed-objects)
sge::image::color::impl::dynamic::format::rgb_c8_4 const
    sge::image::color::impl::dynamic::format::rgbx8{
        mizuiro::color::layout::rgbx{}, sge::image::color::format::rgbx8};

FCPPT_PP_POP_WARNING
