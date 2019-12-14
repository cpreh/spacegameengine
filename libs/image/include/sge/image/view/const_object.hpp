//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_VIEW_CONST_OBJECT_HPP_INCLUDED
#define SGE_IMAGE_VIEW_CONST_OBJECT_HPP_INCLUDED

#include <sge/image/has_format.hpp>
#include <sge/image/mizuiro_color_traits.hpp>
#include <sge/image/detail/instantiate/symbol.hpp>
#include <sge/image/traits/image/color_tag.hpp>
#include <sge/image/view/const_elements.hpp>
#include <sge/image/view/const_object_fwd.hpp>
#include <sge/image/view/mizuiro_type_fwd.hpp>
#include <sge/image/view/object_fwd.hpp>
#include <mizuiro/const_tag.hpp>
#include <fcppt/variant/from_list.hpp>


namespace sge
{
namespace image
{
namespace view
{

template<
	typename Tag
>
class const_object
{
public:
	typedef
	sge::image::view::object<
		Tag
	>
	nonconst_object;

	typedef
	sge::image::view::const_elements<
		Tag
	>
	elements;

	typedef
	fcppt::variant::from_list<
		elements
	>
	variant;

	template<
		typename Format
	>
	explicit
	const_object(
		sge::image::view::mizuiro_type<
			Format,
			mizuiro::const_tag
		> const &_view
	)
	:
		const_object(
			variant{
				_view
			}
		)
	{
		static_assert(
			sge::image::has_format<
				sge::image::traits::image::color_tag<
					Tag
				>,
				typename
				Format::color_format
			>::value,
			"Invalid format."
		);
	}

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	explicit
	const_object(
		variant const &
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	explicit
	const_object(
		nonconst_object const  &
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	const_object(
		const_object const &
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	const_object &
	operator=(
		const_object const &
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	~const_object();

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	variant const &
	get() const;
private:
	variant variant_;
};

}
}
}

#endif
