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


#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/size.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/scoped_planar_lock.hpp>
#include <sge/texture/pos.hpp>
#include <sge/texture/sub_data.hpp>


void
sge::texture::sub_data(
	sge::renderer::texture::planar &_texture,
	sge::image2d::view::const_object const &_view,
	sge::texture::pos const _pos
)
{
	sge::renderer::texture::scoped_planar_lock const lock(
		_texture,
		sge::renderer::lock_rect(
			_pos,
			sge::image2d::view::size(
				_view
			)
		),
		sge::renderer::lock_mode::writeonly
	);

	sge::image2d::algorithm::copy_and_convert(
		_view,
		lock.value(),
		sge::image::algorithm::may_overlap::no
	);
}
