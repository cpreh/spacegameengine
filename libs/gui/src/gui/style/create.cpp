//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/gui/impl/style/simple.hpp>
#include <sge/gui/style/base_unique_ptr.hpp>
#include <sge/gui/style/create.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>

sge::gui::style::base_unique_ptr sge::gui::style::create()
{
  return fcppt::unique_ptr_to_base<sge::gui::style::base>(
      fcppt::make_unique_ptr<sge::gui::impl::style::simple>());
}
