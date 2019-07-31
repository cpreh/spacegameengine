//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_DS_FORMAT_STRIDE_HPP_INCLUDED
#define SGE_IMAGE_DS_FORMAT_STRIDE_HPP_INCLUDED

#include <sge/image/size_type.hpp>
#include <sge/image/ds/format_fwd.hpp>
#include <sge/image/ds/detail/symbol.hpp>


namespace sge
{
namespace image
{
namespace ds
{

SGE_IMAGE_DS_DETAIL_SYMBOL
sge::image::size_type
format_stride(
	sge::image::ds::format
);

}
}
}

#endif
