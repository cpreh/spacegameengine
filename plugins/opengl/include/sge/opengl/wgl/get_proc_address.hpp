//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_WGL_GET_PROC_ADDRESS_HPP_INCLUDED
#define SGE_OPENGL_WGL_GET_PROC_ADDRESS_HPP_INCLUDED

#include <awl/backends/windows/windows.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace opengl
{
namespace wgl
{

PROC get_proc_address(std::string const &);

}
}
}

#endif
