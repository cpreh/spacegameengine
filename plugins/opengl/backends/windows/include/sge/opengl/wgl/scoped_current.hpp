//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_WGL_SCOPED_CURRENT_HPP_INCLUDED
#define SGE_OPENGL_WGL_SCOPED_CURRENT_HPP_INCLUDED

#include <sge/opengl/wgl/context_holder_fwd.hpp>
#include <sge/opengl/wgl/scoped_current_fwd.hpp>
#include <sge/opengl/windows/gdi_device_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opengl
{
namespace wgl
{

class scoped_current
{
  FCPPT_NONCOPYABLE(scoped_current);

public:
  scoped_current(
      sge::opengl::wgl::context_holder const &, sge::opengl::windows::gdi_device const &);

  ~scoped_current();
};

}
}
}

#endif
