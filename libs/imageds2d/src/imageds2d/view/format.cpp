//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/ds/format.hpp>
#include <sge/image/ds/impl/traits/format_map.hpp>
#include <sge/image/ds/traits/format_fwd.hpp>
#include <sge/image/impl/view/format_impl.hpp>
#include <sge/image/impl/view/instantiate_format.hpp>
#include <sge/imageds2d/tag.hpp>
#include <sge/imageds2d/view/const_object.hpp>
#include <sge/imageds2d/view/format.hpp>
#include <sge/imageds2d/view/object.hpp>


sge::image::ds::format
sge::imageds2d::view::format(
	sge::imageds2d::view::object const &_view
)
{
	return
		sge::image::view::format<
			sge::imageds2d::tag
		>(
			_view
		);
}

sge::image::ds::format
sge::imageds2d::view::format(
	sge::imageds2d::view::const_object const &_view
)
{
	return
		sge::image::view::format<
			sge::imageds2d::tag
		>(
			_view
		);
}

SGE_IMAGE_IMPL_VIEW_INSTANTIATE_FORMAT(
	sge::imageds2d::tag
);
