//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/config/app_name.hpp>
#include <sge/config/own_app_name.hpp>
#include <fcppt/text.hpp>

sge::config::app_name sge::config::own_app_name()
{
  return sge::config::app_name(FCPPT_TEXT("spacegameengine"));
}
