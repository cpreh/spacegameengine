//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_XRANDR_SYSTEM_UNIQUE_PTR_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_SYSTEM_UNIQUE_PTR_HPP_INCLUDED

#include <sge/opengl/xrandr/system_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sge
{
namespace opengl
{
namespace xrandr
{

typedef
fcppt::unique_ptr<
	sge::opengl::xrandr::system
>
system_unique_ptr;

}
}
}

#endif
