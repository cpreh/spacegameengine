//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/impl/algorithm/clone_impl.hpp>
#include <sge/image/impl/algorithm/instantiate_clone.hpp>
#include <sge/image3d/tag.hpp>
#include <sge/image3d/algorithm/clone.hpp>
#include <sge/image3d/store/object.hpp>
#include <sge/image3d/view/const_object.hpp>


sge::image3d::store::object
sge::image3d::algorithm::clone(
	sge::image3d::view::const_object const &_view
)
{
	return
		sge::image::algorithm::clone<
			sge::image3d::tag
		>(
			_view
		);
}


SGE_IMAGE_IMPL_ALGORITHM_INSTANTIATE_CLONE(
	sge::image3d::tag
);
