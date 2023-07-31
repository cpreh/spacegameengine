//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_VIEWPORT_FRACTIONAL_ASPECT_HPP_INCLUDED
#define SGE_VIEWPORT_FRACTIONAL_ASPECT_HPP_INCLUDED

#include <sge/viewport/fractional_aspect_fwd.hpp>
#include <sge/viewport/detail/symbol.hpp>
#include <sge/window/unit.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp>

namespace sge::viewport
{

class fractional_aspect
{
public:
  using value_type = sge::window::unit;

  FCPPT_DECLARE_STRONG_TYPEDEF(value_type, num_type);
  FCPPT_DECLARE_STRONG_TYPEDEF(value_type, denom_type);

  SGE_VIEWPORT_DETAIL_SYMBOL
  fractional_aspect(num_type, denom_type);

  [[nodiscard]] SGE_VIEWPORT_DETAIL_SYMBOL value_type num() const;

  [[nodiscard]] SGE_VIEWPORT_DETAIL_SYMBOL value_type denom() const;

private:
  value_type num_;

  value_type denom_;
};

}

#endif
