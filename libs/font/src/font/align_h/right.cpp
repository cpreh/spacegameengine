//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/font/align_h/max_width.hpp>
#include <sge/font/align_h/right.hpp>

sge::font::align_h::right::right(sge::font::align_h::max_width const _max_width)
    : max_width_(_max_width)
{
}

sge::font::align_h::max_width sge::font::align_h::right::max_width() const { return max_width_; }
