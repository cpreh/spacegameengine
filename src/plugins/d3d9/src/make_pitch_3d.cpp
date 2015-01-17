/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
