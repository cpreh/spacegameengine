//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_FONT_ADDED_HPP_INCLUDED
#define SGE_FONT_ADDED_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/font/added_fwd.hpp>
#include <sge/font/detail/symbol.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::font
{

class SGE_CORE_DETAIL_CLASS_SYMBOL added
{
  FCPPT_NONMOVABLE(added);

protected:
  SGE_FONT_DETAIL_SYMBOL
  added();

public:
  SGE_FONT_DETAIL_SYMBOL
  virtual ~added();
};

}

#endif
