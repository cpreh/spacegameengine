//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_EGL_CREATE_DISPLAY_HPP_INCLUDED
#define SGE_OPENGL_EGL_CREATE_DISPLAY_HPP_INCLUDED

#include <sge/opengl/egl/display_unique_ptr.hpp>
#include <awl/system/object_ref.hpp>
#include <fcppt/log/object_reference.hpp>


namespace sge
{
namespace opengl
{
namespace egl
{

sge::opengl::egl::display_unique_ptr
create_display(
	fcppt::log::object_reference,
	awl::system::object_ref
);

}
}
}

#endif
