//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_VIEW_DECLARE_SUB_HPP_INCLUDED
#define SGE_IMAGE_VIEW_DECLARE_SUB_HPP_INCLUDED

#include <sge/image/box_fwd.hpp>
#include <sge/image/detail/instantiate/symbol.hpp>
#include <sge/image/view/const_object_fwd.hpp>
#include <sge/image/view/object_fwd.hpp>
#include <sge/image/view/sub.hpp>


#define SGE_IMAGE_VIEW_DECLARE_SUB(\
	tag\
)\
extern \
template \
SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL \
sge::image::view::object< \
	tag \
> \
sge::image::view::sub( \
	sge::image::view::object< \
		tag \
	> const &, \
	sge::image::box< \
		tag \
	> const & \
); \
\
extern \
template \
SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL \
sge::image::view::const_object< \
	tag \
> \
sge::image::view::sub( \
	sge::image::view::const_object< \
		tag \
	> const &, \
	sge::image::box< \
		tag \
	> const & \
)

#endif
