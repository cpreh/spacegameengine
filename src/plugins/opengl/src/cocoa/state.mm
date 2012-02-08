#include <sge/opengl/cocoa/state.hpp>
#include <sge/opengl/cocoa/SGECocoaOpenGLView.hpp>
#include <awl/backends/cocoa/window/instance.hpp>

sge::opengl::cocoa::state::state(
	opengl::context::object &,
	renderer::parameters const &_parameters,
	renderer::adapter,
	awl::backends::cocoa::window::instance &_window)
{
	NSWindow *w = _window.window_handle();

	opengl_view_ = [[SGECocoaOpenGLView alloc] initWithFrame:[w frame] andParameters:_parameters];
	[w setContentView:opengl_view_];

	NSLog(@"Created state.");
}

sge::opengl::cocoa::state::~state()
{
}

void
sge::opengl::cocoa::state::begin_rendering()
{
	[opengl_view_ beginRendering];
}

void
sge::opengl::cocoa::state::swap_buffers()
{
	[opengl_view_ swapBuffers];
}
