//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_WGL_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_WGL_CONTEXT_HPP_INCLUDED

#include <sge/opengl/backend/context.hpp>
#include <sge/opengl/backend/current_unique_ptr.hpp>
#include <sge/opengl/wgl/context_fwd.hpp>
#include <sge/opengl/wgl/context_holder.hpp>
#include <sge/opengl/windows/gdi_device.hpp>
#include <awl/backends/windows/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opengl
{
namespace wgl
{

class context : public sge::opengl::backend::context
{
  FCPPT_NONCOPYABLE(context);

public:
  explicit context(awl::backends::windows::window::object &);

  ~context() override;

private:
  sge::opengl::backend::current_unique_ptr activate() override;

  void deactivate(sge::opengl::backend::current_unique_ptr &&) override;

  sge::opengl::windows::gdi_device const gdi_device_;

  sge::opengl::wgl::context_holder const context_;
};

}
}
}

#endif
