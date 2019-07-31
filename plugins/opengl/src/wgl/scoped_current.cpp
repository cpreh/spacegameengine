//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/wgl/context_holder.hpp>
#include <sge/opengl/wgl/make_current.hpp>
#include <sge/opengl/wgl/scoped_current.hpp>
#include <sge/opengl/windows/gdi_device.hpp>


sge::opengl::wgl::scoped_current::scoped_current(
	sge::opengl::wgl::context_holder const &_context,
	sge::opengl::windows::gdi_device const &_gdi_device
)
{
	sge::opengl::wgl::make_current(
		_gdi_device.hdc(),
		_context.get()
	);
}

sge::opengl::wgl::scoped_current::~scoped_current()
{
	// TODO: Function
	sge::opengl::wgl::make_current(
		nullptr,
		nullptr
	);
}
