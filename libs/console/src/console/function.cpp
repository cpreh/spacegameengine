//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/console/function.hpp>
#include <sge/console/long_description.hpp>
#include <sge/console/short_description.hpp>
#include <sge/console/signal.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::console::function::function(
    sge::console::short_description &&_short_description,
    sge::console::long_description &&_long_description)
    : signal_(),
      short_description_(std::move(_short_description)),
      long_description_(std::move(_long_description))
{
}

sge::console::function::function(function &&) noexcept = default;

sge::console::function &sge::console::function::operator=(function &&) noexcept = default;

sge::console::function::~function() = default;

sge::console::signal &sge::console::function::signal() { return signal_; }

sge::console::short_description const &sge::console::function::short_description() const
{
  return short_description_;
}

sge::console::long_description const &sge::console::function::long_description() const
{
  return long_description_;
}
