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


#include <sge/image2d/tag.hpp>
#include <sge/image2d/algorithm/compare.hpp>
#include <sge/image2d/traits/const_view_fwd.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/src/image/algorithm/compare_impl.hpp>
#include <sge/src/image/algorithm/instantiate_compare.hpp>


bool
sge::image2d::algorithm::compare(
	sge::image2d::view::const_object const &_src1,
	sge::image2d::view::const_object const &_src2
)
{
	return
		sge::image::algorithm::compare<
			sge::image2d::tag
		>(
			_src1,
			_src2
		);
}

SGE_SRC_IMAGE_ALGORITHM_INSTANTIATE_COMPARE(
	sge::image2d::tag
);
