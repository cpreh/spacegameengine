//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_VIEW_BASIC_FORMAT_C_HPP_INCLUDED
#define SGE_IMAGE_VIEW_BASIC_FORMAT_C_HPP_INCLUDED

#include <sge/image/view/basic_format.hpp>


namespace sge
{
namespace image
{
namespace view
{

template<
	typename Dim,
	typename ColorFormat
>
using
basic_format_c
=
sge::image::view::basic_format<
	Dim::value,
	ColorFormat
>;

}
}
}

#endif
