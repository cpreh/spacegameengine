//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/glx/visual/object.hpp>
#include <sge/renderer/visual_base.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/backends/x11/visual/info_unique_ptr.hpp>
#include <awl/backends/x11/visual/wrapped.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::opengl::glx::visual::object::object(
    awl::backends::x11::visual::info_unique_ptr &&_info,
    sge::renderer::pixel_format::object const &_pixel_format)
    : awl::backends::x11::visual::wrapped(std::move(_info)),
      sge::renderer::visual_base(_pixel_format)
{
}

sge::opengl::glx::visual::object::~object() = default;
