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


#ifndef SGE_X11INPUT_XIM_GET_IC_VALUES_HPP_INCLUDED
#define SGE_X11INPUT_XIM_GET_IC_VALUES_HPP_INCLUDED

#include <sge/input/exception.hpp>
#include <sge/x11input/xim/context.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace x11input
{
namespace xim
{

template<
	typename... Args
>
void
get_ic_values(
	sge::x11input::xim::context const &_context,
	Args &&... _args
)
{
	char const *const result{
		::XGetICValues(
			_context.get(),
			std::forward<
				Args
			>(
				_args
			)...,
			NULL
		)
	};

	if(
		result
		!=
		nullptr
	)
		throw
			sge::input::exception{
				FCPPT_TEXT("XGetICValues failed with ")
				+
				fcppt::from_std_string(
					result
				)
			};
}

}
}
}

#endif
