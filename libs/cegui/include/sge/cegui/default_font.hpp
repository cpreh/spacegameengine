//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CEGUI_DEFAULT_FONT_HPP_INCLUDED
#define SGE_CEGUI_DEFAULT_FONT_HPP_INCLUDED

#include <sge/cegui/font_size.hpp>
#include <sge/cegui/detail/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

namespace sge::cegui
{

class default_font
{
public:
  SGE_CEGUI_DETAIL_SYMBOL
  default_font(std::filesystem::path &&, sge::cegui::font_size);

  [[nodiscard]] std::filesystem::path const &path() const;

  [[nodiscard]] sge::cegui::font_size font_size() const;

private:
  std::filesystem::path path_;

  sge::cegui::font_size font_size_;
};

}

#endif
