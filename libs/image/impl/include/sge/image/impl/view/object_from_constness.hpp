//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_IMPL_VIEW_OBJECT_FROM_CONSTNESS_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_OBJECT_FROM_CONSTNESS_HPP_INCLUDED

#include <sge/image/view/const_object_fwd.hpp>
#include <sge/image/view/object_fwd.hpp>
#include <mizuiro/choose_const.hpp>


namespace sge::image::impl::view
{

template<
	typename Tag,
	typename Constness
>
using
object_from_constness
=
mizuiro::choose_const<
	Constness,
	sge::image::view::object<
		Tag
	>,
	sge::image::view::const_object<
		Tag
	>
>;

}

#endif
