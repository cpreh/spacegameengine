//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_DS_INIT_DETAIL_MAKE_HPP_INCLUDED
#define SGE_IMAGE_DS_INIT_DETAIL_MAKE_HPP_INCLUDED

#include <mizuiro/color/init/make.hpp>


#define SGE_IMAGE_DS_INIT_DETAIL_MAKE(\
	name\
)\
MIZUIRO_COLOR_INIT_MAKE(\
	sge::image::ds::channel,\
	name\
)

#endif
