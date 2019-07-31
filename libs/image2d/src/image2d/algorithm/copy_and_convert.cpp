//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/color/impl/traits/dynamic_copy_and_convert.hpp>
#include <sge/image/color/impl/traits/static_converter.hpp>
#include <sge/image/impl/algorithm/copy_and_convert_impl.hpp>
#include <sge/image/impl/algorithm/instantiate_copy_and_convert.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/tag.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/traits/color_tag.hpp>
#include <sge/image2d/traits/dimension.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/object.hpp>


void
sge::image2d::algorithm::copy_and_convert(
	sge::image2d::view::const_object const &_src,
	sge::image2d::view::object const &_dest,
	sge::image::algorithm::may_overlap const _overlap,
	sge::image::algorithm::uninitialized const _uninitialized
)
{
	sge::image::algorithm::copy_and_convert<
		sge::image2d::tag
	>(
		_src,
		_dest,
		_overlap,
		_uninitialized
	);
}

SGE_IMAGE_IMPL_ALGORITHM_INSTANTIATE_COPY_AND_CONVERT(
	sge::image2d::tag
);
