//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/windows/gdi_device.hpp>
#include <sge/opengl/windows/visual/choose_format.hpp>
#include <sge/opengl/windows/visual/format.hpp>
#include <sge/renderer/exception.hpp>
#include <awl/backends/windows/windows.hpp>
#include <fcppt/text.hpp>


sge::opengl::windows::visual::format const
sge::opengl::windows::visual::choose_format(
	sge::opengl::windows::gdi_device const &_device,
	PIXELFORMATDESCRIPTOR const &_format_desc
)
{
	int const ret(
		::ChoosePixelFormat(
			_device.hdc(),
			&_format_desc
		)
	);

	if(
		ret == 0
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("ChoosePixelFormat() failed")
		);

	return
		sge::opengl::windows::visual::format(
			ret
		);
}
