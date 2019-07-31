//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_VIEW_SUB_HPP_INCLUDED
#define SGE_IMAGE_VIEW_SUB_HPP_INCLUDED

#include <sge/image/box_fwd.hpp>
#include <sge/image/detail/instantiate/symbol.hpp>
#include <sge/image/view/const_object_fwd.hpp>
#include <sge/image/view/object_fwd.hpp>


namespace sge
{
namespace image
{
namespace view
{

template<
	typename Tag
>
SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
sge::image::view::object<
	Tag
>
sub(
	sge::image::view::object<
		Tag
	> const &,
	sge::image::box<
		Tag
	> const &
);

template<
	typename Tag
>
SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
sge::image::view::const_object<
	Tag
>
sub(
	sge::image::view::const_object<
		Tag
	> const &,
	sge::image::box<
		Tag
	> const &
);

}
}
}

#endif
