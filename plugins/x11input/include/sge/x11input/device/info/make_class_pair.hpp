//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_DEVICE_INFO_MAKE_CLASS_PAIR_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_INFO_MAKE_CLASS_PAIR_HPP_INCLUDED

#include <fcppt/mpl/map/element.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


#define SGE_X11INPUT_DEVICE_INFO_MAKE_CLASS_PAIR(\
	name\
)\
fcppt::mpl::map::element<\
	name ## Info ,\
	std::integral_constant<\
		int,\
		name \
	>\
>

#endif
