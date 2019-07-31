//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/windows/gdi_device.hpp>
#include <sge/renderer/exception.hpp>
#include <awl/backends/windows/windows.hpp>
#include <fcppt/text.hpp>


sge::opengl::windows::gdi_device::gdi_device(
	HWND const _hwnd,
	sge::opengl::windows::gdi_device::get_tag
)
:
	hwnd_(
		_hwnd
	),
	dc_(
		::GetDC(
			_hwnd
		)
	)
{
	if(
		dc_
		==
		nullptr
	)
		throw
			sge::renderer::exception(
				FCPPT_TEXT("GetDC() failed!")
			);
}

sge::opengl::windows::gdi_device::~gdi_device()
{
	::ReleaseDC(
		hwnd_,
		dc_
	);
}

HDC
sge::opengl::windows::gdi_device::hdc() const
{
	return
		dc_;
}
