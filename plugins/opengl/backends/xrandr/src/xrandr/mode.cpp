//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/xrandr/mode.hpp>
#include <sge/opengl/xrandr/mode_index.hpp>
#include <sge/opengl/xrandr/refresh_rate.hpp>
#include <sge/opengl/xrandr/rotation.hpp>

sge::opengl::xrandr::mode::mode(
    sge::opengl::xrandr::mode_index const _index,
    sge::opengl::xrandr::rotation const _rotation,
    sge::opengl::xrandr::refresh_rate const _rate)
    : index_{_index}, rotation_{_rotation}, rate_{_rate}
{
}

sge::opengl::xrandr::mode_index sge::opengl::xrandr::mode::index() const { return index_; }

sge::opengl::xrandr::rotation sge::opengl::xrandr::mode::rotation() const { return rotation_; }

sge::opengl::xrandr::refresh_rate sge::opengl::xrandr::mode::rate() const { return rate_; }
