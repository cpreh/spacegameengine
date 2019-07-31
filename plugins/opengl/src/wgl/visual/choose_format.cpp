//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/call_fun_ref.hpp>
#include <sge/opengl/wgl/visual/attribute_container.hpp>
#include <sge/opengl/wgl/visual/choose_format.hpp>
#include <sge/opengl/wgl/visual/config.hpp>
#include <sge/opengl/wgl/visual/make_attributes.hpp>
#include <sge/opengl/wgl/visual/pixel_format_types.hpp>
#include <sge/opengl/windows/gdi_device.hpp>
#include <sge/opengl/windows/visual/format.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/backends/windows/windows.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/to_exception.hpp>


sge::opengl::windows::visual::format
sge::opengl::wgl::visual::choose_format(
	sge::opengl::windows::gdi_device const &_device,
	sge::opengl::wgl::visual::config const &_config,
	sge::renderer::pixel_format::object const &_format
)
{
	sge::opengl::wgl::visual::attribute_container const attributes(
		sge::opengl::wgl::visual::make_attributes(
			_config,
			_format
		)
	);

	sge::opengl::wgl::visual::pixel_format_types const pixel_format_types(
		fcppt::optional::to_exception(
			_config.pixel_format_types(),
			[]{
				return
					sge::renderer::unsupported(
						FCPPT_TEXT("WGL pixel formats"),
						FCPPT_TEXT(""),
						FCPPT_TEXT("WGLEW_EXT_pixel_format, WGLEW_ARB_pixel_format")
					);
			}
		)
	);

	int result;

	UINT num_results;

	if(
		sge::opengl::call_fun_ref(
			pixel_format_types.choose_pixel_format(),
			_device.hdc(),
			attributes.data(),
			static_cast<
				FLOAT const *
			>(
				nullptr
			),
			1u,
			&result,
			&num_results
		)
		==
		FALSE
	)
		throw
			sge::renderer::exception(
				FCPPT_TEXT("wglChoosePixelFormat failed!")
			);

	return
		sge::opengl::windows::visual::format(
			result
		);
}
