//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PANGO_EXTENTS_HPP_INCLUDED
#define SGE_PANGO_EXTENTS_HPP_INCLUDED

#include <sge/pango/extents_fwd.hpp>
#include <sge/pango/ink_rect.hpp>
#include <sge/pango/logical_rect.hpp>

namespace sge::pango
{

class extents
{
public:
  extents(sge::pango::ink_rect, sge::pango::logical_rect);

  [[nodiscard]] sge::pango::ink_rect ink_rect() const;

  [[nodiscard]] sge::pango::logical_rect logical_rect() const;

private:
  sge::pango::ink_rect ink_rect_;

  sge::pango::logical_rect logical_rect_;
};

}

#endif
