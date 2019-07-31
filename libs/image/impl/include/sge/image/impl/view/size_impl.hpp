//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_IMPL_VIEW_SIZE_IMPL_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_SIZE_IMPL_HPP_INCLUDED

#include <sge/image/dim.hpp>
#include <sge/image/impl/view/size_any.hpp>
#include <sge/image/view/const_object_fwd.hpp>
#include <sge/image/view/object_fwd.hpp>
#include <sge/image/view/size.hpp>


template<
	typename Tag
>
sge::image::dim<
	Tag
>
sge::image::view::size(
	sge::image::view::object<
		Tag
	> const &_view
)
{
	return
		sge::image::impl::view::size_any<
			Tag
		>(
			_view
		);
}

template<
	typename Tag
>
sge::image::dim<
	Tag
>
sge::image::view::size(
	sge::image::view::const_object<
		Tag
	> const &_view
)
{
	return
		sge::image::impl::view::size_any<
			Tag
		>(
			_view
		);
}

#endif
