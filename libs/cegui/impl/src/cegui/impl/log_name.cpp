//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cegui/impl/log_name.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/name.hpp>

fcppt::log::name sge::cegui::impl::log_name() { return fcppt::log::name{FCPPT_TEXT("cegui")}; }
