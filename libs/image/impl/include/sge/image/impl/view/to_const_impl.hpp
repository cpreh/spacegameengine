//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_IMPL_VIEW_TO_CONST_IMPL_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_TO_CONST_IMPL_HPP_INCLUDED

#include <sge/image/view/const_object.hpp>
#include <sge/image/view/object.hpp>
#include <sge/image/view/to_const.hpp>
#include <mizuiro/image/make_const_view.hpp>
#include <fcppt/variant/apply.hpp>


template<
	typename Tag
>
sge::image::view::const_object<
	Tag
>
sge::image::view::to_const(
	sge::image::view::object<
		Tag
	> const &_src
)
{
	return
		fcppt::variant::apply(
			[](
				auto const &_src_inner
			)
			{
				return
					sge::image::view::const_object<
						Tag
					>(
						mizuiro::image::make_const_view(
							_src_inner
						)
					);
			},
			_src.get()
		);
}

#endif
