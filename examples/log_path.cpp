//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/config/app_name.hpp>
#include <sge/config/company_name.hpp>
#include <sge/config/log_path.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cout.hpp>

int main()
{
  fcppt::io::cout() << sge::config::log_path(
                           sge::config::company_name(FCPPT_TEXT("spacegameengine")),
                           sge::config::app_name(FCPPT_TEXT("log_path")))
                    << FCPPT_TEXT('\n');
}
