#ifndef SGE_OPENGL_COCOA_CREATE_DEVICE_STATE_HPP_INCLUDED
#define SGE_OPENGL_COCOA_CREATE_DEVICE_STATE_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/device_state_ptr.hpp>
#include <sge/renderer/parameters_fwd.hpp>
#include <sge/renderer/adapter.hpp>
#include <awl/window/instance_fwd.hpp>

namespace sge
{
namespace opengl
{
namespace cocoa
{
sge::opengl::device_state_ptr
create_device_state(
	opengl::context::object &,
	renderer::parameters const &,
	renderer::adapter,
	awl::window::instance &);
}
}
}

#endif
