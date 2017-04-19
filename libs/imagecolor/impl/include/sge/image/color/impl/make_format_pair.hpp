/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


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
