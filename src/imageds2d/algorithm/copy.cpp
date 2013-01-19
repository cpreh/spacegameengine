/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/image/ds/traits/format_fwd.hpp>
#include <sge/imageds2d/tag.hpp>
#include <sge/imageds2d/algorithm/copy.hpp>
#include <sge/imageds2d/traits/color_tag.hpp>
#include <sge/imageds2d/traits/const_view_fwd.hpp>
#include <sge/imageds2d/traits/view_fwd.hpp>
#include <sge/imageds2d/view/const_object.hpp>
#include <sge/imageds2d/view/object.hpp>
#include <sge/src/image/algorithm/copy_impl.hpp>
#include <sge/src/image/algorithm/instantiate_copy.hpp>


void
sge::imageds2d::algorithm::copy(
	sge::imageds2d::view::const_object const &_src,
	sge::imageds2d::view::object const &_dest,
	sge::image::algorithm::may_overlap const _overlap
)
{
	sge::image::algorithm::copy<
		sge::imageds2d::tag
	>(
		_src,
		_dest,
		_overlap
	);
}

SGE_SRC_IMAGE_ALGORITHM_INSTANTIATE_COPY(
	sge::imageds2d::tag
);
