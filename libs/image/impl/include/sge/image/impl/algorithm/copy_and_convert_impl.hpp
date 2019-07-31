//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
