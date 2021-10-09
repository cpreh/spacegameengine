//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_FONT_SYSTEM_HPP_INCLUDED
#define SGE_FONT_SYSTEM_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/font/added_unique_ptr.hpp>
#include <sge/font/object_unique_ptr.hpp>
#include <sge/font/parameters_fwd.hpp>
#include <sge/font/system_fwd.hpp>
#include <sge/font/detail/symbol.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

namespace sge::font
{

class SGE_CORE_DETAIL_CLASS_SYMBOL system
{
  FCPPT_NONMOVABLE(system);

protected:
  SGE_FONT_DETAIL_SYMBOL
  system();

public:
  SGE_FONT_DETAIL_SYMBOL
  virtual ~system();

  [[nodiscard]] virtual sge::font::object_unique_ptr create_font(sge::font::parameters const &) = 0;

  [[nodiscard]] virtual sge::font::added_unique_ptr add_font(std::filesystem::path const &) = 0;
};

}

#endif
