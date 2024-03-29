//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CORE_EXCEPTION_HPP_INCLUDED
#define SGE_CORE_EXCEPTION_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/core/detail/symbol.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>

namespace sge::core
{

class SGE_CORE_DETAIL_CLASS_SYMBOL exception : public fcppt::exception
{
public:
  SGE_CORE_DETAIL_SYMBOL
  explicit exception(fcppt::string &&);

  SGE_CORE_DETAIL_SYMBOL
  exception(exception &&) noexcept;

  SGE_CORE_DETAIL_SYMBOL
  exception(exception const &);

  SGE_CORE_DETAIL_SYMBOL
  exception &operator=(exception &&) noexcept;

  SGE_CORE_DETAIL_SYMBOL
  exception &operator=(exception const &);

  SGE_CORE_DETAIL_SYMBOL
  ~exception() noexcept override;
};

}

#endif
