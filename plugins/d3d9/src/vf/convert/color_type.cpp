//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/vf/convert/color_type.hpp>
#include <sge/image/color/format_stride.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/vf/dynamic/color.hpp>
#include <fcppt/text.hpp>


D3DDECLTYPE
sge::d3d9::vf::convert::color_type(
	sge::renderer::vf::dynamic::color const &_color
)
{
	if(
		sge::image::color::format_stride(
			_color.color_format()
		)
		!=
		4u
	)
		throw sge::renderer::unsupported(
			FCPPT_TEXT("D3D9 can only use colors with a 4 bytes size!"),
			FCPPT_TEXT(""),
			FCPPT_TEXT("")
		);

	return D3DDECLTYPE_D3DCOLOR;
}
