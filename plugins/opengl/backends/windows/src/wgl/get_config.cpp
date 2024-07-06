//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/wgl/config.hpp>
#include <sge/opengl/wgl/context_holder.hpp>
#include <sge/opengl/wgl/extension_set.hpp>
#include <sge/opengl/wgl/get_config.hpp>
#include <sge/opengl/wgl/get_extensions.hpp>
#include <sge/opengl/wgl/scoped_current.hpp>
#include <sge/opengl/wgl/visual/config.hpp>
#include <sge/opengl/windows/gdi_device.hpp>
#include <sge/renderer/exception.hpp>
#include <awl/backends/windows/window/object.hpp>
#include <awl/system/object.hpp>
#include <awl/visual/object.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <awl/window/object.hpp>
#include <awl/window/object_unique_ptr.hpp>
#include <awl/window/parameters.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/optional/to_exception.hpp>

sge::opengl::wgl::config sge::opengl::wgl::get_config(awl::system::object &_awl_system)
{
  awl::visual::object_unique_ptr const visual(_awl_system.default_visual());

  awl::window::object_unique_ptr const window(_awl_system.create_window(
      awl::window::parameters(*visual).class_name(FCPPT_TEXT("sgeopengl_dummy_window"))));

  sge::opengl::windows::gdi_device const gdi_device(
      fcppt::optional::to_exception(
          fcppt::cast::dynamic<awl::backends::windows::window::object>(*window),
          []
          {
            return sge::renderer::exception{
                FCPPT_TEXT("Window passed to opengl::wgl::get_config is not a Windows window.")};
          })
          ->hwnd(),
      sge::opengl::windows::gdi_device::get_tag());

  sge::opengl::wgl::context_holder const context(gdi_device);

  sge::opengl::wgl::scoped_current const current(context, gdi_device);

  sge::opengl::wgl::extension_set const extensions(sge::opengl::wgl::get_extensions(current));

  return sge::opengl::wgl::config(sge::opengl::wgl::visual::config(extensions, current));
}
