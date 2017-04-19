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


#ifndef SGE_IMAGE_IMPL_ALGORITHM_COPY_AND_CONVERT_IMPL_HPP_INCLUDED
#define SGE_IMAGE_IMPL_ALGORITHM_COPY_AND_CONVERT_IMPL_HPP_INCLUDED

#include <sge/image/algorithm/copy_and_convert.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/view/const_object_fwd.hpp>
#include <sge/image/view/object_fwd.hpp>
#include <sge/image/impl/config.hpp>

#if defined(SGE_IMAGE_STATIC_COPY_AND_CONVERT)
#include <sge/image/impl/algorithm/copy_and_convert_static.hpp>
#else
#include <sge/image/impl/algorithm/copy_and_convert_dynamic.hpp>
#endif


template<
	typename Tag
>
void
sge::image::algorithm::copy_and_convert(
	sge::image::view::const_object<
		Tag
	> const &_src,
	sge::image::view::object<
		Tag
	> const &_dest,
	sge::image::algorithm::may_overlap const _overlap,
	sge::image::algorithm::uninitialized const _uninitialized
)
{
	// TODO: automatically use the static version if the dynamic one is not specialized
#if defined(SGE_IMAGE_STATIC_COPY_AND_CONVERT)
	sge::image::impl::algorithm::copy_and_convert_static<
		Tag
	>(
		_src,
		_dest,
		_overlap,
		_uninitialized
	);
#else
	sge::image::impl::algorithm::copy_and_convert_dynamic<
		Tag
	>(
		_src,
		_dest,
		_overlap,
		_uninitialized
	);
#endif
}

#endif
