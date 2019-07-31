//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/windows/gdi_device.hpp>
#include <sge/opengl/windows/visual/format.hpp>
#include <sge/opengl/windows/visual/set_format.hpp>
#include <sge/renderer/exception.hpp>
#include <awl/backends/windows/windows.hpp>
#include <fcppt/text.hpp>


void
sge::opengl::windows::visual::set_format(
	sge::opengl::windows::gdi_device const &_device,
	sge::opengl::windows::visual::format const _format,
	PIXELFORMATDESCRIPTOR const &_format_desc
)
{
	if(
		::SetPixelFormat(
			_device.hdc(),
			_format.get(),
			&_format_desc
		)
		== FALSE
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("SetPixelFormat() failed")
		);
}
