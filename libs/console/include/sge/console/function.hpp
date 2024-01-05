//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CONSOLE_FUNCTION_HPP_INCLUDED
#define SGE_CONSOLE_FUNCTION_HPP_INCLUDED

#include <sge/console/function_fwd.hpp>
#include <sge/console/long_description.hpp>
#include <sge/console/short_description.hpp>
#include <sge/console/signal_fwd.hpp>
#include <sge/console/detail/symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/object_decl.hpp> // IWYU pragma: keep
#include <fcppt/signal/unregister/base_decl.hpp> // IWYU pragma: keep

namespace sge::console
{

class function
{
  FCPPT_NONCOPYABLE(function);

public:
  SGE_CONSOLE_DETAIL_SYMBOL
  function(sge::console::short_description &&, sge::console::long_description &&);

  SGE_CONSOLE_DETAIL_SYMBOL
  function(function &&) noexcept;

  SGE_CONSOLE_DETAIL_SYMBOL
  function &operator=(function &&) noexcept;

  SGE_CONSOLE_DETAIL_SYMBOL
  ~function();

  SGE_CONSOLE_DETAIL_SYMBOL
  sge::console::signal &signal();

  SGE_CONSOLE_DETAIL_SYMBOL
  sge::console::short_description const &short_description() const;

  SGE_CONSOLE_DETAIL_SYMBOL
  sge::console::long_description const &long_description() const;

private:
  sge::console::signal signal_;

  sge::console::short_description short_description_;

  sge::console::long_description long_description_;
};

}

#endif
