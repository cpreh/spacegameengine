//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/impl/view/instantiate_size.hpp>
#include <sge/image/impl/view/size_impl.hpp>
#include <sge/image3d/dim.hpp>
#include <sge/image3d/tag.hpp>
#include <sge/image3d/view/const_object.hpp>
#include <sge/image3d/view/object.hpp>
#include <sge/image3d/view/size.hpp>


sge::image3d::dim
sge::image3d::view::size(
	sge::image3d::view::object const &_view
)
{
	return
		sge::image::view::size<
			sge::image3d::tag
		>(
			_view
		);
}

sge::image3d::dim
sge::image3d::view::size(
	sge::image3d::view::const_object const &_view
)
{
	return
		sge::image::view::size<
			sge::image3d::tag
		>(
			_view
		);
}

SGE_IMAGE_IMPL_VIEW_INSTANTIATE_SIZE(
	sge::image3d::tag
);
