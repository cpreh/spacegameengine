//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_FONT_TEXT_PARAMETERS_HPP_INCLUDED
#define SGE_FONT_TEXT_PARAMETERS_HPP_INCLUDED

#include <sge/font/flags_field.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/align_h/variant.hpp>
#include <sge/font/detail/symbol.hpp>

namespace sge::font
{

class text_parameters
{
public:
  // TODO(philipp):
  // - Add gravity for Japanese text
  SGE_FONT_DETAIL_SYMBOL
  explicit text_parameters(sge::font::align_h::variant const &);

  SGE_FONT_DETAIL_SYMBOL
  sge::font::text_parameters &flags(sge::font::flags_field const &);

  [[nodiscard]] SGE_FONT_DETAIL_SYMBOL sge::font::align_h::variant const &align_h() const;

  [[nodiscard]] SGE_FONT_DETAIL_SYMBOL sge::font::flags_field const &flags() const;

private:
  sge::font::align_h::variant align_h_;

  sge::font::flags_field flags_;
};

}

#endif
