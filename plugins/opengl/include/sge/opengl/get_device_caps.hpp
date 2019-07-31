//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_GET_DEVICE_CAPS_HPP_INCLUDED
#define SGE_OPENGL_GET_DEVICE_CAPS_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/renderer/caps/device.hpp>


namespace sge
{
namespace opengl
{

sge::renderer::caps::device
get_device_caps(
	sge::opengl::context::object &
);

}
}

#endif
