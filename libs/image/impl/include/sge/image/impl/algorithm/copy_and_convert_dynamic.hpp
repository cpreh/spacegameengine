//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_IMPL_ALGORITHM_COPY_AND_CONVERT_DYNAMIC_HPP_INCLUDED
#define SGE_IMAGE_IMPL_ALGORITHM_COPY_AND_CONVERT_DYNAMIC_HPP_INCLUDED

#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/impl/traits/dynamic_copy_and_convert.hpp>
#include <sge/image/traits/image/color_tag.hpp>
#include <sge/image/view/const_object_fwd.hpp>
#include <sge/image/view/object_fwd.hpp>


namespace sge
{
namespace image
{
namespace impl
{
namespace algorithm
{

template<
	typename Tag
>
inline
void
copy_and_convert_dynamic(
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
	sge::image::impl::traits::dynamic_copy_and_convert<
		sge::image::traits::image::color_tag<
			Tag
		>
	>:: template execute<
		Tag
	>(
		_src,
		_dest,
		_overlap,
		_uninitialized
	);
}

}
}
}
}

#endif
