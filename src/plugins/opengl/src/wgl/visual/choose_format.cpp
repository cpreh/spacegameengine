/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/opengl/context/use.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/wgl/visual/attribute_container.hpp>
#include <sge/opengl/wgl/visual/choose_format.hpp>
#include <sge/opengl/wgl/visual/context.hpp>
#include <sge/opengl/wgl/visual/make_attributes.hpp>
#include <sge/opengl/wgl/visual/optional_pixel_format_types.hpp>
#include <sge/opengl/windows/gdi_device.hpp>
#include <sge/opengl/windows/visual/format.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/backends/windows/windows.hpp>
#include <fcppt/null_ptr.hpp>
#include <fcppt/text.hpp>


sge::opengl::windows::visual::format const
sge::opengl::wgl::visual::choose_format(
	sge::opengl::windows::gdi_device const &_device,
	sge::opengl::context::system::object &_system_context,
	sge::renderer::pixel_format::object const &_format
)
{
	sge::opengl::wgl::visual::attribute_container const attributes(
		sge::opengl::wgl::visual::make_attributes(
			_system_context,
			_format
		)
	);

	sge::opengl::wgl::visual::context &context(
		sge::opengl::context::use<
			sge::opengl::wgl::visual::context
		>(
			_system_context
		)
	);

	sge::opengl::wgl::visual::optional_pixel_format_types const pixel_format_types(
		context.pixel_format_types()
	);

	if(
		!pixel_format_types
	)
		throw sge::renderer::unsupported(
			FCPPT_TEXT("WGL pixel formats"),
			FCPPT_TEXT(""),
			FCPPT_TEXT("WGLEW_EXT_pixel_format, WGLEW_ARB_pixel_format")
		);

	int result;
	
	UINT num_results;

	if(
		pixel_format_types->choose_pixel_format()(
			_device.hdc(),
			attributes.data(),
			fcppt::null_ptr(),
			1u,
			&result,
			&num_results
		)
		== FALSE
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("wglChoosePixelFormat failed!")
		);

	return
		sge::opengl::windows::visual::format(
			result
		);
}
