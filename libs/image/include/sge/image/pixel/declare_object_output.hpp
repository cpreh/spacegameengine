//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_PIXEL_DECLARE_OBJECT_OUTPUT_HPP_INCLUDED
#define SGE_IMAGE_PIXEL_DECLARE_OBJECT_OUTPUT_HPP_INCLUDED

#include <sge/image/detail/instantiate/symbol.hpp>
#include <sge/image/pixel/object_fwd.hpp>
#include <sge/image/pixel/object_output.hpp>
#include <fcppt/io/ostream_fwd.hpp>


#define SGE_IMAGE_PIXEL_DECLARE_OBJECT_OUTPUT(\
	tag\
)\
extern \
template \
SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL \
fcppt::io::ostream & \
sge::image::pixel::operator<< < \
	tag \
>( \
	fcppt::io::ostream &, \
	sge::image::pixel::object< \
		tag \
	> const & \
)

#endif
