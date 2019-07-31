//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_COLOR_IMPL_MAKE_FORMAT_PAIR_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_MAKE_FORMAT_PAIR_HPP_INCLUDED

#include <sge/image/color/format.hpp>
#include <sge/image/color/impl/format_pair.hpp>
#include <sge/image/impl/make_format_pair.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/comma_if.hpp>
#include <fcppt/config/external_end.hpp>


#define SGE_IMAGE_COLOR_IMPL_MAKE_FORMAT_PAIR(\
	s,\
	_,\
	index,\
	name\
)\
BOOST_PP_COMMA_IF(\
	index\
) \
SGE_IMAGE_IMPL_MAKE_FORMAT_PAIR(\
	color,\
	name\
)

#endif
