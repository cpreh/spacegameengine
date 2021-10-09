//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/x11input/xim/lc_ctype.hpp>
#include <fcppt/getenv.hpp>
#include <fcppt/optional_std_string.hpp>
#include <fcppt/optional/alternative.hpp>

fcppt::optional_std_string sge::x11input::xim::lc_ctype()
{
  return fcppt::optional::alternative(
      fcppt::optional::alternative(
          fcppt::getenv("LC_ALL"), [] { return fcppt::getenv("LC_CTYPE"); }),
      [] { return fcppt::getenv("LANG"); });
}
