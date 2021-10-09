//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CONSOLE_GFX_CURSOR_HPP_INCLUDED
#define SGE_CONSOLE_GFX_CURSOR_HPP_INCLUDED

#include <sge/console/function_map.hpp>
#include <sge/console/prefix.hpp>
#include <sge/console/gfx/cursor_fwd.hpp>
#include <sge/console/gfx/detail/symbol.hpp>
#include <sge/font/char_type.hpp>
#include <sge/font/string.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::console::gfx
{

class cursor
{
  FCPPT_NONMOVABLE(cursor);

public:
  SGE_CONSOLE_GFX_DETAIL_SYMBOL
  cursor();

  SGE_CONSOLE_GFX_DETAIL_SYMBOL
  ~cursor();

  [[nodiscard]] SGE_CONSOLE_GFX_DETAIL_SYMBOL sge::font::string edited() const;

  [[nodiscard]] SGE_CONSOLE_GFX_DETAIL_SYMBOL sge::font::string const &string() const;

  SGE_CONSOLE_GFX_DETAIL_SYMBOL
  void string(sge::font::string const &);

  SGE_CONSOLE_GFX_DETAIL_SYMBOL
  void erase_word();

  SGE_CONSOLE_GFX_DETAIL_SYMBOL
  void erase_char();

  SGE_CONSOLE_GFX_DETAIL_SYMBOL
  void left();

  SGE_CONSOLE_GFX_DETAIL_SYMBOL
  void right();

  SGE_CONSOLE_GFX_DETAIL_SYMBOL
  void to_start();

  SGE_CONSOLE_GFX_DETAIL_SYMBOL
  void to_end();

  [[nodiscard]] SGE_CONSOLE_GFX_DETAIL_SYMBOL bool empty() const;

  SGE_CONSOLE_GFX_DETAIL_SYMBOL
  void insert(sge::font::char_type);

  SGE_CONSOLE_GFX_DETAIL_SYMBOL
  void complete_word(sge::console::prefix, sge::console::function_map const &);

private:
  sge::font::string line_;

  using size_type = sge::font::string::size_type;

  size_type pos_;
};

}

#endif
