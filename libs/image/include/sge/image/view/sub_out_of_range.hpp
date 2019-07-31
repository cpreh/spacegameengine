//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_VIEW_SUB_OUT_OF_RANGE_HPP_INCLUDED
#define SGE_IMAGE_VIEW_SUB_OUT_OF_RANGE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/image/box.hpp>
#include <sge/image/exception.hpp>
#include <sge/image/detail/instantiate/symbol.hpp>
#include <sge/image/view/sub_out_of_range_fwd.hpp>


namespace sge
{
namespace image
{
namespace view
{

template<
	typename Tag
>
class SGE_CORE_DETAIL_CLASS_SYMBOL sub_out_of_range
:
	public sge::image::exception
{
public:
	typedef
	sge::image::box<
		Tag
	>
	box;

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	sub_out_of_range(
		box const &outer,
		box const &inner
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	sub_out_of_range(
		sub_out_of_range &&
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	sub_out_of_range(
		sub_out_of_range const &
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	sub_out_of_range &
	operator=(
		sub_out_of_range &&
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	sub_out_of_range &
	operator=(
		sub_out_of_range const &
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	box const &
	outer() const;

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	box const &
	inner() const;

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	~sub_out_of_range() noexcept
	override;
private:
	box
		outer_,
		inner_;
};

}
}
}

#endif
