//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/pango/extents.hpp>
#include <sge/pango/ink_rect.hpp>
#include <sge/pango/logical_rect.hpp>

sge::pango::extents::extents(
    sge::pango::ink_rect const _ink_rect, sge::pango::logical_rect const _logical_rect)
    : ink_rect_{_ink_rect}, logical_rect_{_logical_rect}
{
}

sge::pango::ink_rect sge::pango::extents::ink_rect() const { return ink_rect_; }

sge::pango::logical_rect sge::pango::extents::logical_rect() const { return logical_rect_; }
