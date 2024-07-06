//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_WINDOWS_GDI_DEVICE_HPP_INCLUDED
#define SGE_OPENGL_WINDOWS_GDI_DEVICE_HPP_INCLUDED

#include <sge/opengl/windows/gdi_device_fwd.hpp>
#include <awl/backends/windows/windows.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opengl
{
namespace windows
{

class gdi_device
{
  FCPPT_NONCOPYABLE(gdi_device);

public:
  struct get_tag
  {
  };

  gdi_device(HWND, get_tag);

  ~gdi_device();

  HDC hdc() const;

private:
  HWND hwnd_;

  HDC dc_;
};

}
}
}

#endif
