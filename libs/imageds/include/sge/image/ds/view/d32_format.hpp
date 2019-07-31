//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_DS_VIEW_D32_FORMAT_HPP_INCLUDED
#define SGE_IMAGE_DS_VIEW_D32_FORMAT_HPP_INCLUDED

#include <sge/image/size_type.hpp>
#include <sge/image/ds/d32_format.hpp>
#include <sge/image/view/basic_format.hpp>


namespace sge
{
namespace image
{
namespace ds
{
namespace view
{

template<
	sge::image::size_type Dim
>
using d32_format
=
sge::image::view::basic_format<
	Dim,
	sge::image::ds::d32_format
>;

}
}
}
}

#endif
