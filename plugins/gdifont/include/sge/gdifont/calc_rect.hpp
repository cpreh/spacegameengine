//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_GDIFONT_CALC_RECT_HPP_INCLUDED
#define SGE_GDIFONT_CALC_RECT_HPP_INCLUDED

#include <sge/font/rect_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/align_h/variant_fwd.hpp>
#include <sge/gdifont/device_context_fwd.hpp>
#include <sge/gdifont/format.hpp>
#include <sge/gdifont/include_windows.hpp>

namespace sge
{
namespace gdifont
{

sge::font::rect calc_rect(
    sge::gdifont::device_context const &,
    HFONT,
    sge::font::string const &,
    sge::font::align_h::variant const &,
    sge::gdifont::format);

}
}

#endif
