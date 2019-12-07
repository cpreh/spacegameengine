//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_DS_STATIC_FORMATS_HPP_INCLUDED
#define SGE_IMAGE_DS_STATIC_FORMATS_HPP_INCLUDED

#include <sge/image/ds/d16_format.hpp>
#include <sge/image/ds/d24s8_format.hpp>
#include <sge/image/ds/d32_format.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image
{
namespace ds
{

typedef
metal::list<
	sge::image::ds::d16_format,
	sge::image::ds::d32_format,
	sge::image::ds::d24s8_format
>
static_formats;

}
}
}

#endif
