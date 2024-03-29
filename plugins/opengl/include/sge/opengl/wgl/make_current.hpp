//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_WGL_MAKE_CURRENT_HPP_INCLUDED
#define SGE_OPENGL_WGL_MAKE_CURRENT_HPP_INCLUDED

#include <awl/backends/windows/windows.hpp>

namespace sge
{
namespace opengl
{
namespace wgl
{

void make_current(HDC, HGLRC);

}
}
}

#endif
