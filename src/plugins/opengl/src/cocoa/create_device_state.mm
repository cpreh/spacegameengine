#include <sge/opengl/cocoa/create_device_state.hpp>
#include <sge/opengl/cocoa/state.hpp>
#include <awl/backends/cocoa/window/instance.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/cref.hpp>

sge::opengl::device_state_ptr
sge::opengl::cocoa::create_device_state(
	opengl::context::object &_context,
	renderer::parameters const &_parameters,
	renderer::adapter const _adapter,
	awl::window::instance &_window)
{
	return
		opengl::device_state_ptr(
			fcppt::make_unique_ptr<cocoa::state>(
				fcppt::ref(
					_context),
				fcppt::cref(
					_parameters),
				_adapter,
				fcppt::ref(
					dynamic_cast<awl::backends::cocoa::window::instance &>(
						_window))));
}
