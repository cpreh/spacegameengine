//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_GUI_NEEDED_WIDTH_FROM_STRINGS_HPP_INCLUDED
#define SGE_GUI_NEEDED_WIDTH_FROM_STRINGS_HPP_INCLUDED

#include <sge/font/object_fwd.hpp>
#include <sge/gui/needed_width.hpp>
#include <sge/gui/string_container.hpp>
#include <sge/gui/detail/symbol.hpp>

namespace sge::gui
{

SGE_GUI_DETAIL_SYMBOL
sge::gui::needed_width needed_width_from_strings(
    sge::font::object &, // NOLINT(google-runtime-references)
    sge::gui::string_container const &);

}

#endif
