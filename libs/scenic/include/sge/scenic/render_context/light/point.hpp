//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SCENIC_RENDER_CONTEXT_LIGHT_POINT_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_LIGHT_POINT_HPP_INCLUDED

#include <sge/scenic/detail/symbol.hpp>
#include <sge/scenic/render_context/light/attenuation.hpp>
#include <sge/scenic/render_context/light/point_fwd.hpp> // IWYU pragma: keep
#include <sge/scenic/render_context/light/position.hpp>

namespace sge::scenic::render_context::light
{
class point
{
public:
  SGE_SCENIC_DETAIL_SYMBOL
  point(
      sge::scenic::render_context::light::position,
      sge::scenic::render_context::light::attenuation const &);

  [[nodiscard]] SGE_SCENIC_DETAIL_SYMBOL sge::scenic::render_context::light::position const &
  position() const;

  [[nodiscard]] SGE_SCENIC_DETAIL_SYMBOL sge::scenic::render_context::light::attenuation const &
  attenuation() const;

private:
  sge::scenic::render_context::light::position position_;
  sge::scenic::render_context::light::attenuation attenuation_;
};
}

#endif
