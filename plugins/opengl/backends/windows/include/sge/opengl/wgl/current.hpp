//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_WGL_CURRENT_HPP_INCLUDED
#define SGE_OPENGL_WGL_CURRENT_HPP_INCLUDED

#include <sge/opengl/backend/current.hpp>
#include <sge/opengl/backend/fun_ptr.hpp>
#include <sge/opengl/windows/gdi_device.hpp>
#include <sge/renderer/display_mode/vsync_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace opengl
{
namespace wgl
{

class current : public sge::opengl::backend::current
{
  FCPPT_NONCOPYABLE(current);

public:
  explicit current(sge::opengl::windows::gdi_device const &);

  ~current() override;

private:
  sge::opengl::backend::fun_ptr load_function(std::string const &) const override;

  void begin_rendering() override;

  void end_rendering() override;

  void vsync(sge::renderer::display_mode::vsync) override;

  sge::opengl::windows::gdi_device const &gdi_device_;
};

}
}
}

#endif
