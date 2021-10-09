//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/libpng/extension.hpp>
#include <sge/media/extension.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>

sge::media::extension sge::libpng::extension()
{
  return sge::media::extension{fcppt::string{FCPPT_TEXT("png")}};
}
