//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/impl/view/instantiate_sub.hpp>
#include <sge/image/impl/view/sub_impl.hpp>
#include <sge/image2d/rect.hpp>
#include <sge/image2d/tag.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/image2d/view/sub.hpp>


sge::image2d::view::object
sge::image2d::view::sub(
	sge::image2d::view::object const &_src,
	sge::image2d::rect const &_rect
)
{
	return
		sge::image::view::sub<
			sge::image2d::tag
		>(
			_src,
			_rect
		);
}

sge::image2d::view::const_object
sge::image2d::view::sub(
	sge::image2d::view::const_object const &_src,
	sge::image2d::rect const &_rect
)
{
	return
		sge::image::view::sub<
			sge::image2d::tag
		>(
			_src,
			_rect
		);
}

SGE_IMAGE_IMPL_VIEW_INSTANTIATE_SUB(
	sge::image2d::tag
);
