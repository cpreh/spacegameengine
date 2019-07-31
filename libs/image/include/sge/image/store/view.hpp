//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_STORE_VIEW_HPP_INCLUDED
#define SGE_IMAGE_STORE_VIEW_HPP_INCLUDED

#include <sge/image/detail/instantiate/symbol.hpp>
#include <sge/image/store/object_fwd.hpp>
#include <sge/image/view/const_object_fwd.hpp>
#include <sge/image/view/object_fwd.hpp>


namespace sge
{
namespace image
{
namespace store
{

template<
	typename Tag
>
SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
sge::image::view::object<
	Tag
>
view(
	sge::image::store::object<
		Tag
	> &
);

template<
	typename Tag
>
SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
sge::image::view::const_object<
	Tag
>
view(
	sge::image::store::object<
		Tag
	> const &
);

}
}
}

#endif
