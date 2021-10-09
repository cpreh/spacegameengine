//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SCENIC_RENDER_CONTEXT_FOG_PROPERTIES_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_FOG_PROPERTIES_HPP_INCLUDED

#include <sge/scenic/detail/symbol.hpp>
#include <sge/scenic/render_context/fog/color.hpp>
#include <sge/scenic/render_context/fog/end.hpp>
#include <sge/scenic/render_context/fog/start.hpp>

namespace sge::scenic::render_context::fog
{
class properties
{
public:
  SGE_SCENIC_DETAIL_SYMBOL
  properties(
      sge::scenic::render_context::fog::start const &,
      sge::scenic::render_context::fog::end const &,
      sge::scenic::render_context::fog::color);

  [[nodiscard]] SGE_SCENIC_DETAIL_SYMBOL sge::scenic::render_context::fog::start const &
  start() const;

  [[nodiscard]] SGE_SCENIC_DETAIL_SYMBOL sge::scenic::render_context::fog::end const &end() const;

  [[nodiscard]] SGE_SCENIC_DETAIL_SYMBOL sge::scenic::render_context::fog::color const &
  color() const;

private:
  sge::scenic::render_context::fog::start start_;
  sge::scenic::render_context::fog::end end_;
  sge::scenic::render_context::fog::color color_;
};
}

#endif
