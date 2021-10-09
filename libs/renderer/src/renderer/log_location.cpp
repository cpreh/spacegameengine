//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/log/location.hpp>
#include <sge/renderer/log_location.hpp>
#include <sge/renderer/impl/log_name.hpp>
#include <fcppt/log/location.hpp>

fcppt::log::location sge::renderer::log_location()
{
  return sge::log::location() / sge::renderer::impl::log_name();
}
