//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/from_d3d_pitch.hpp>
#include <sge/d3d9/make_pitch_3d.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image3d/dim_fwd.hpp>
#include <sge/image3d/pitch.hpp>


sge::image3d::pitch const
sge::d3d9::make_pitch_3d(
	D3DLOCKED_BOX const &_box,
	sge::image3d::dim const &_dim,
	sge::image::color::format const _format
)
{
	return
		sge::d3d9::from_d3d_pitch<
			3
		>(
			sge::image3d::pitch(
				_box.RowPitch,
				_box.SlicePitch
			),
			_dim,
			_format
		);
}
