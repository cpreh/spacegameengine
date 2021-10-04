//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_IMPL_VIEW_CHECKED_SUB_CONDITION_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_CHECKED_SUB_CONDITION_HPP_INCLUDED

#include <sge/image/box.hpp>
#include <sge/image/view/size.hpp>
#include <sge/image/view/sub_out_of_range.hpp>
#include <fcppt/math/box/contains.hpp>
#include <fcppt/math/vector/null.hpp>


namespace sge::image::impl::view
{

template<
	typename Tag,
	typename View
>
void
checked_sub_condition(
	View const &_src,
	sge::image::box<
		Tag
	> const &_box
)
noexcept(
	false
)
{
	using
	box
	=
	sge::image::box<
		Tag
	>;

	box const outer(
		fcppt::math::vector::null<
			typename
			box::vector
		>(),
		sge::image::view::size<
			Tag
		>(
			_src
		)
	);

	if(
		!fcppt::math::box::contains(
			outer,
			_box
		)
	)
	{
		throw
			sge::image::view::sub_out_of_range<
				Tag
			>{
				outer,
				_box
			};
	}
}

}

#endif
