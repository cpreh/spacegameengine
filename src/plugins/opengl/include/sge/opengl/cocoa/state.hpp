#ifndef SGE_OPENGL_COCOA_STATE_HPP_INCLUDED
#define SGE_OPENGL_COCOA_STATE_HPP_INCLUDED

#include <awl/backends/cocoa/window/instance_fwd.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/device_state.hpp>
#include <sge/renderer/adapter.hpp>
#include <sge/renderer/parameters_fwd.hpp>
#include <fcppt/noncopyable.hpp>

@class SGECocoaOpenGLView;

namespace sge
{
namespace opengl
{
namespace cocoa
{
class state
:
	public opengl::device_state
{
FCPPT_NONCOPYABLE(
	state);
public:
	explicit
	state(
		opengl::context::object &,
		renderer::parameters const &,
		renderer::adapter,
		awl::backends::cocoa::window::instance &);

	~state();

	void
	begin_rendering();

	void
	swap_buffers();
private:
	SGECocoaOpenGLView *opengl_view_;
};
}
}
}

#endif
