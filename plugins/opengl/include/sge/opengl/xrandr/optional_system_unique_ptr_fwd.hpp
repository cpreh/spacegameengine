//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_XRANDR_OPTIONAL_SYSTEM_UNIQUE_PTR_FWD_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_OPTIONAL_SYSTEM_UNIQUE_PTR_FWD_HPP_INCLUDED

#include <sge/opengl/xrandr/system_unique_ptr.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sge::opengl::xrandr
{

using
optional_system_unique_ptr
=
fcppt::optional::object<
	sge::opengl::xrandr::system_unique_ptr
>;

}

#endif
