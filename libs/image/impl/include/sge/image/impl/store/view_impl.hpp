//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_IMPL_STORE_VIEW_IMPL_HPP_INCLUDED
#define SGE_IMAGE_IMPL_STORE_VIEW_IMPL_HPP_INCLUDED

#include <sge/image/impl/store/view_any.hpp>
#include <sge/image/store/object_fwd.hpp>
#include <sge/image/store/view.hpp>
#include <sge/image/view/const_object.hpp>
#include <sge/image/view/object.hpp>
#include <fcppt/reference_impl.hpp>


template<
	typename Tag
>
sge::image::view::object<
	Tag
>
sge::image::store::view(
	fcppt::reference<
		sge::image::store::object<
			Tag
		>
	> const _store
)
{
	return
		sge::image::impl::store::view_any<
			sge::image::view::object<
				Tag
			>
		>(
			_store
		);
}

template<
	typename Tag
>
sge::image::view::const_object<
	Tag
>
sge::image::store::view(
	fcppt::reference<
		sge::image::store::object<
			Tag
		> const
	> const _store
)
{
	return
		sge::image::impl::store::view_any<
			sge::image::view::const_object<
				Tag
			>
		>(
			_store
		);
}

#endif
