//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/color/format.hpp>
#include <sge/renderer/texture/color_format.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/renderer/texture/translate_srgb_emulation.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::image::color::format
sge::renderer::texture::translate_srgb_emulation(
	sge::renderer::texture::color_format const &_color_format
)
{
	sge::image::color::format const format(
		_color_format.format()
	);

	if(
		_color_format.emulate_srgb()
		==
		sge::renderer::texture::emulate_srgb::no
	)
	{
		return
			format;
	}

	switch(
		format
	)
	{
	case sge::image::color::format::a8:
	case sge::image::color::format::l8:
	case sge::image::color::format::la8:
	case sge::image::color::format::rgb8:
	case sge::image::color::format::bgr8:
	case sge::image::color::format::rgba8:
	case sge::image::color::format::rgbx8:
	case sge::image::color::format::bgra8:
	case sge::image::color::format::bgrx8:
	case sge::image::color::format::r32f:
	case sge::image::color::format::bgr32f:
	case sge::image::color::format::rgb32f:
	case sge::image::color::format::rgba32f:
	case sge::image::color::format::bgra32f:
		return
			format;
	case sge::image::color::format::srgb8:
		return
			sge::image::color::format::rgb8;
	case sge::image::color::format::srgba8:
		return
			sge::image::color::format::rgba8;
	case sge::image::color::format::sbgr8:
		return
			sge::image::color::format::bgr8;
	case sge::image::color::format::sbgra8:
		return
			sge::image::color::format::bgra8;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
