//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_FONT_TEXT_HPP_INCLUDED
#define SGE_FONT_TEXT_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/font/dim_fwd.hpp>
#include <sge/font/index.hpp>
#include <sge/font/optional_index_fwd.hpp>
#include <sge/font/optional_rect_fwd.hpp>
#include <sge/font/rect_fwd.hpp>
#include <sge/font/text_fwd.hpp>
#include <sge/font/vector_fwd.hpp>
#include <sge/font/view_fwd.hpp>
#include <sge/font/detail/symbol.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::font
{

class SGE_CORE_DETAIL_CLASS_SYMBOL text
{
  FCPPT_NONMOVABLE(text);

protected:
  SGE_FONT_DETAIL_SYMBOL
  text();

public:
  SGE_FONT_DETAIL_SYMBOL
  virtual ~text();

  virtual void render(sge::font::view const &) = 0;

  [[nodiscard]] virtual sge::font::rect rect() const = 0;

  [[nodiscard]] virtual sge::font::dim logical_size() const = 0;

  [[nodiscard]] virtual sge::font::optional_rect cursor_rect(sge::font::index) const = 0;

  [[nodiscard]] virtual sge::font::optional_index pos_to_index(sge::font::vector) const = 0;
};

}

#endif
