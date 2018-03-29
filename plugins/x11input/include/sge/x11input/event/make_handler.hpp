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


#ifndef SGE_X11INPUT_EVENT_MAKE_HANDLER_HPP_INCLUDED
#define SGE_X11INPUT_EVENT_MAKE_HANDLER_HPP_INCLUDED

#include <sge/x11input/event/concrete_handler.hpp>
#include <sge/x11input/event/handler.hpp>
#include <sge/x11input/event/static_type.hpp>
#include <sge/x11input/event/type.hpp>
#include <awl/backends/x11/system/event/generic.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace x11input
{
namespace event
{

template<
	typename Type,
	typename Event
>
std::pair<
	sge::x11input::event::type,
	sge::x11input::event::handler
>
make_handler(
	sge::x11input::event::concrete_handler<
		Event
	> _function
)
{
	return
		std::make_pair(
			sge::x11input::event::type{
				Type::value
			},
			sge::x11input::event::handler{
				[
					_function
				](
					awl::backends::x11::system::event::generic const &_event
				)
				{
					typedef
					sge::x11input::event::static_type<
						Type
					>
					event_type;

					static_assert(
						std::is_same<
							event_type,
							Event
						>::value,
						"Event types do not match"
					);

					return
						_function(
							*fcppt::cast::from_void_ptr<
								Event const *
							>(
								_event.data()
							)
						);
				}
			}
		);
}

}
}
}

#endif
