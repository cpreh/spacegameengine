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


#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/color/impl/traits/dynamic_copy_and_convert.hpp>
#include <sge/image/color/impl/traits/static_converter.hpp>
#include <sge/image/impl/algorithm/copy_and_convert_impl.hpp>
#include <sge/image/impl/algorithm/instantiate_copy_and_convert.hpp>
#include <sge/image3d/dim.hpp>
#include <sge/image3d/tag.hpp>
#include <sge/image3d/algorithm/copy_and_convert.hpp>
#include <sge/image3d/traits/color_tag.hpp>
#include <sge/image3d/traits/const_view_fwd.hpp>
#include <sge/image3d/traits/dim_fwd.hpp>
#include <sge/image3d/traits/view_fwd.hpp>
#include <sge/image3d/view/const_object.hpp>
#include <sge/image3d/view/object.hpp>


void
sge::image3d::algorithm::copy_and_convert(
	sge::image3d::view::const_object const &_src,
	sge::image3d::view::object const &_dest,
	sge::image::algorithm::may_overlap const _overlap,
	sge::image::algorithm::uninitialized const _uninitialized
)
{
	sge::image::algorithm::copy_and_convert<
		sge::image3d::tag
	>(
		_src,
		_dest,
		_overlap,
		_uninitialized
	);
}

SGE_IMAGE_IMPL_ALGORITHM_INSTANTIATE_COPY_AND_CONVERT(
	sge::image3d::tag
);
