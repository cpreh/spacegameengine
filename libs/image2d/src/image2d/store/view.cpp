//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/impl/store/instantiate_view.hpp>
#include <sge/image/impl/store/view_impl.hpp>
#include <sge/image2d/tag.hpp>
#include <sge/image2d/store/object.hpp>
#include <sge/image2d/store/view.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/object.hpp>


sge::image2d::view::object
sge::image2d::store::view(
	sge::image2d::store::object &_store
)
{
	return
		sge::image::store::view<
			sge::image2d::tag
		>(
			_store
		);
}

sge::image2d::view::const_object
sge::image2d::store::view(
	sge::image2d::store::object const &_store
)
{
	return
		sge::image::store::view<
			sge::image2d::tag
		>(
			_store
		);
}
