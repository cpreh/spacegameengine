//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_DS_IMPL_FORMAT_MAP_HPP_INCLUDED
#define SGE_IMAGE_DS_IMPL_FORMAT_MAP_HPP_INCLUDED

#include <sge/image/ds/d16_format.hpp>
#include <sge/image/ds/d24s8_format.hpp>
#include <sge/image/ds/d32_format.hpp>
#include <sge/image/ds/impl/make_format_pair.hpp>
#include <sge/image/impl/format_map.hpp>


namespace sge
{
namespace image
{
namespace ds
{
namespace impl
{

using
format_map
=
sge::image::impl::format_map<
	SGE_IMAGE_DS_IMPL_MAKE_FORMAT_PAIR(
		d16
	),
	SGE_IMAGE_DS_IMPL_MAKE_FORMAT_PAIR(
		d24s8
	),
	SGE_IMAGE_DS_IMPL_MAKE_FORMAT_PAIR(
		d32
	)
>;

}
}
}
}

#endif
