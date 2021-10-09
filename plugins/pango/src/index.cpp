//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/pango/index.hpp>

sge::pango::index::index(
    sge::pango::index::result_type const _result, sge::pango::index::trailing_type const _trailing)
    : result_{_result}, trailing_{_trailing}
{
}

sge::pango::index::result_type sge::pango::index::result() const { return result_; }

sge::pango::index::trailing_type sge::pango::index::trailing() const { return trailing_; }
