//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/visual/rgb_triple.hpp>

sge::opengl::visual::rgb_triple::rgb_triple(
    sge::opengl::visual::rgb_triple::red_bits const _red,
    sge::opengl::visual::rgb_triple::green_bits const _green,
    sge::opengl::visual::rgb_triple::blue_bits const _blue)
    : red_(_red), green_(_green), blue_(_blue)
{
}

sge::opengl::visual::rgb_triple::red_bits sge::opengl::visual::rgb_triple::red() const
{
  return red_;
}

sge::opengl::visual::rgb_triple::green_bits sge::opengl::visual::rgb_triple::green() const
{
  return green_;
}

sge::opengl::visual::rgb_triple::blue_bits sge::opengl::visual::rgb_triple::blue() const
{
  return blue_;
}
