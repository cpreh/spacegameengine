//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_WGL_GET_EXTENSIONS_HPP_INCLUDED
#define SGE_OPENGL_WGL_GET_EXTENSIONS_HPP_INCLUDED

#include <sge/opengl/wgl/extension_set.hpp>
#include <sge/opengl/wgl/scoped_current_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace wgl
{

sge::opengl::wgl::extension_set
get_extensions(
	sge::opengl::wgl::scoped_current const &
);

}
}
}

#endif
