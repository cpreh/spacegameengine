//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/font/log_location.hpp>
#include <sge/font/bitmap/log_location.hpp>
#include <sge/font/bitmap/impl/log_name.hpp>
#include <fcppt/log/location.hpp>

fcppt::log::location sge::font::bitmap::log_location()
{
  return sge::font::log_location() / sge::font::bitmap::impl::log_name();
}
