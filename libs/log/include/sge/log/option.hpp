//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_LOG_OPTION_HPP_INCLUDED
#define SGE_LOG_OPTION_HPP_INCLUDED

#include <sge/log/option_fwd.hpp> // IWYU pragma: keep
#include <sge/log/detail/symbol.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/location.hpp>

namespace sge::log
{

class option
{
public:
  SGE_LOG_DETAIL_SYMBOL
  option(fcppt::log::location &&, fcppt::log::level);

  [[nodiscard]] fcppt::log::location const &location() const;

  [[nodiscard]] fcppt::log::level level() const;

private:
  fcppt::log::location location_;

  fcppt::log::level level_;
};

}

#endif
