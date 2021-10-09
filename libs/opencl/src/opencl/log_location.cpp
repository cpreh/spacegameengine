//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/log/location.hpp>
#include <sge/opencl/log_location.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/name.hpp>

fcppt::log::location sge::opencl::log_location()
{
  return sge::log::location() / fcppt::log::name{FCPPT_TEXT("opencl")};
}
