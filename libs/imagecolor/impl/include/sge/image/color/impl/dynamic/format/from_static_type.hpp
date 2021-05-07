//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_COLOR_IMPL_DYNAMIC_FORMAT_FROM_STATIC_TYPE_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_DYNAMIC_FORMAT_FROM_STATIC_TYPE_HPP_INCLUDED

#include <sge/image/color/impl/dynamic/format/from_static.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


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
namespace format
{

template<
	typename Format
>
using from_static_type
=
std::remove_cvref_t<
	decltype(
		sge::image::color::impl::dynamic::format::from_static(
			std::declval<
				Format
			>()
		)
	)
>;

}
}
}
}
}
}

#endif
