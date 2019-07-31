//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/backend/context.hpp>
#include <sge/opengl/backend/current.hpp>
#include <sge/opengl/backend/current_unique_ptr.hpp>
#include <sge/opengl/wgl/context.hpp>
#include <sge/opengl/wgl/current.hpp>
#include <sge/opengl/wgl/make_current.hpp>
#include <sge/opengl/windows/gdi_device.hpp>
#include <awl/backends/windows/window/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sge::opengl::wgl::context::context(
	awl::backends::windows::window::object &_window
)
:
	sge::opengl::backend::context(),
	gdi_device_(
		_window.hwnd(),
		sge::opengl::windows::gdi_device::get_tag()
	),
	context_(
		gdi_device_
	)
{
}

sge::opengl::wgl::context::~context()
{
}

sge::opengl::backend::current_unique_ptr
sge::opengl::wgl::context::activate()
{
	sge::opengl::wgl::make_current(
		gdi_device_.hdc(),
		context_.get()
	);

	return
		fcppt::unique_ptr_to_base<
			sge::opengl::backend::current
		>(
			fcppt::make_unique_ptr<
				sge::opengl::wgl::current
			>(
				gdi_device_
			)
		);
}

void
sge::opengl::wgl::context::deactivate(
	sge::opengl::backend::current_unique_ptr &&
)
{
	sge::opengl::wgl::make_current(
		nullptr,
		nullptr
	);
}
