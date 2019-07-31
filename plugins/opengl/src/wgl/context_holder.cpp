//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/wgl/context_holder.hpp>
#include <sge/opengl/windows/gdi_device.hpp>
#include <sge/renderer/exception.hpp>
#include <awl/backends/windows/windows.hpp>
#include <fcppt/text.hpp>


sge::opengl::wgl::context_holder::context_holder(
	sge::opengl::windows::gdi_device const &_gdi_device
)
:
	glrc_(
		::wglCreateContext(
			_gdi_device.hdc()
		)
	)
{
	if(
		glrc_
		==
		nullptr
	)
		throw
			sge::renderer::exception{
				FCPPT_TEXT("wglCreateContext() failed!")
			};
}

sge::opengl::wgl::context_holder::~context_holder()
{
	::wglDeleteContext(
		glrc_
	);
}

HGLRC
sge::opengl::wgl::context_holder::get() const
{
	return
		glrc_;
}
