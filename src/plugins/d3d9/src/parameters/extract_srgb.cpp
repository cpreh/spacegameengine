/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/d3d9/visual.hpp>
#include <sge/d3d9/parameters/extract_srgb.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <awl/visual/object.hpp>
#include <fcppt/const.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/cast/try_dynamic.hpp>


sge::renderer::pixel_format::srgb
sge::d3d9::parameters::extract_srgb(
	awl::visual::object const &_visual
)
{
	return
		fcppt::optional::maybe(
			fcppt::cast::try_dynamic<
				sge::d3d9::visual const
			>(
				_visual
			),
			fcppt::const_(
				sge::renderer::pixel_format::srgb::no
			),
			[](
				fcppt::reference<
					sge::d3d9::visual const
				> const _d3d_visual
			)
			{
				return
					_d3d_visual.get().pixel_format().srgb();
			}
		);
}
