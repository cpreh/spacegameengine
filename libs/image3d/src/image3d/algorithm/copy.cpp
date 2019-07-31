//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/color/invalid_copy.hpp>
#include <sge/image/color/traits/format_fwd.hpp>
#include <sge/image/impl/algorithm/copy_impl.hpp>
#include <sge/image/impl/algorithm/instantiate_copy.hpp>
#include <sge/image3d/tag.hpp>
#include <sge/image3d/algorithm/copy.hpp>
#include <sge/image3d/view/const_object.hpp>
#include <sge/image3d/view/format.hpp>
#include <sge/image3d/view/object.hpp>


void
sge::image3d::algorithm::copy(
	sge::image3d::view::const_object const &_src,
	sge::image3d::view::object const &_dest,
	sge::image::algorithm::may_overlap const _overlap,
	sge::image::algorithm::uninitialized const _uninitialized
)
{
	sge::image::algorithm::copy<
		sge::image3d::tag
	>(
		_src,
		_dest,
		_overlap,
		_uninitialized
	);
}

SGE_IMAGE_IMPL_ALGORITHM_INSTANTIATE_COPY(
	sge::image3d::tag
);
