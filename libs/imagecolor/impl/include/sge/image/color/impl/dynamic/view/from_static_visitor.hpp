//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_COLOR_IMPL_DYNAMIC_VIEW_FROM_STATIC_VISITOR_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_DYNAMIC_VIEW_FROM_STATIC_VISITOR_HPP_INCLUDED

#include <sge/image/size_type.hpp>
#include <sge/image/color/impl/dynamic/view/basic_variant.hpp>
#include <sge/image/color/impl/dynamic/view/from_static.hpp>


namespace sge
{
namespace image
{
namespace color
{
namespace impl
{
namespace dynamic
{
namespace view
{

template<
	sge::image::size_type Dim,
	typename Constness
>
struct from_static_visitor
{
	typedef
	sge::image::color::impl::dynamic::view::basic_variant<
		Dim,
		Constness
	>
	result_type;

	template<
		typename View
	>
	result_type
	operator()(
		View const &_view
	) const
	{
		return
			result_type(
				sge::image::color::impl::dynamic::view::from_static(
					_view
				)
			);
	}
};

}
}
}
}
}
}

#endif
