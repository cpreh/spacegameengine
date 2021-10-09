//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/egl/major_version.hpp>
#include <sge/opengl/egl/minor_version.hpp>
#include <sge/opengl/egl/version.hpp>

sge::opengl::egl::version::version(
    sge::opengl::egl::major_version const _major, sge::opengl::egl::minor_version const _minor)
    : major_(_major), minor_(_minor)
{
}

sge::opengl::egl::major_version sge::opengl::egl::version::major() const { return major_; }

sge::opengl::egl::minor_version sge::opengl::egl::version::minor() const { return minor_; }
