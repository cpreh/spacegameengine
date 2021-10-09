//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/scenic/render_context/fog/color.hpp>
#include <sge/scenic/render_context/fog/end.hpp>
#include <sge/scenic/render_context/fog/properties.hpp>
#include <sge/scenic/render_context/fog/start.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::scenic::render_context::fog::properties::properties(
    sge::scenic::render_context::fog::start const &_start,
    sge::scenic::render_context::fog::end const &_end,
    sge::scenic::render_context::fog::color _color)
    : start_(_start), end_(_end), color_(std::move(_color))
{
}

sge::scenic::render_context::fog::start const &
sge::scenic::render_context::fog::properties::start() const
{
  return start_;
}

sge::scenic::render_context::fog::end const &
sge::scenic::render_context::fog::properties::end() const
{
  return end_;
}

sge::scenic::render_context::fog::color const &
sge::scenic::render_context::fog::properties::color() const
{
  return color_;
}
