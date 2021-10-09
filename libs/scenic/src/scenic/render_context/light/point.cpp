//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/scenic/render_context/light/attenuation.hpp>
#include <sge/scenic/render_context/light/point.hpp>
#include <sge/scenic/render_context/light/position.hpp>

sge::scenic::render_context::light::point::point(
    sge::scenic::render_context::light::position const _position,
    sge::scenic::render_context::light::attenuation const &_attenuation)
    : position_(_position), attenuation_(_attenuation)
{
}

sge::scenic::render_context::light::position const &
sge::scenic::render_context::light::point::position() const
{
  return position_;
}

sge::scenic::render_context::light::attenuation const &
sge::scenic::render_context::light::point::attenuation() const
{
  return attenuation_;
}
