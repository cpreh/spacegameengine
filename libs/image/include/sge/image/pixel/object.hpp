//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_PIXEL_OBJECT_HPP_INCLUDED
#define SGE_IMAGE_PIXEL_OBJECT_HPP_INCLUDED

#include <sge/image/has_format.hpp>
#include <sge/image/mizuiro_color_traits.hpp>
#include <sge/image/detail/instantiate/symbol.hpp>
#include <sge/image/pixel/elements.hpp>
#include <sge/image/pixel/mizuiro_type_fwd.hpp>
#include <sge/image/pixel/object_fwd.hpp>
#include <fcppt/variant/from_list.hpp>


namespace sge
{
namespace image
{
namespace pixel
{

template<
	typename Tag
>
class object
{
public:
	typedef
	sge::image::pixel::elements<
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
	object(
		sge::image::pixel::mizuiro_type<
			Format
		> const &_color
	)
	:
		object(
			variant{
				_color
			}
		)
	{
		static_assert(
			sge::image::has_format<
				Tag,
				Format
			>::value,
			"Invalid format."
		);
	}

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	explicit
	object(
		variant const &
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	object(
		object const &
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	object &
	operator=(
		object const &
	);

	SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
	~object();

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
