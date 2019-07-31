//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_COLOR_IMPL_FORMAT_PAIR_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_FORMAT_PAIR_HPP_INCLUDED

#include <sge/image/color/format.hpp>
#include <sge/image/impl/format_pair.hpp>


namespace sge
{
namespace image
{
namespace color
{
namespace impl
{

template<
	sge::image::color::format FormatValue,
	typename Format
>
using
format_pair
=
sge::image::impl::format_pair<
	sge::image::color::format,
	FormatValue,
	Format
>;

}
}
}
}

#endif
