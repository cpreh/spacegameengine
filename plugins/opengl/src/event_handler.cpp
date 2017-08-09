
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


#include <sge/opengl/event_handler.hpp>
#include <sge/renderer/event/render.hpp>
#include <sge/window/system_event_function.hpp>
#include <awl/event/base.hpp>
#include <awl/event/container.hpp>
#include <awl/timer/match.hpp>
#include <awl/timer/object_fwd.hpp>
#include <awl/window/object_fwd.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/optional/to_container.hpp>


sge::window::system_event_function
sge::opengl::event_handler(
	awl::window::object &_window,
	awl::timer::object const &_timer
)
{
	// TODO: Check for changed refresh rate
	return
		sge::window::system_event_function{
			[
				&_window,
				&_timer
			](
				awl::event::base const &_event
			)
			{
				return
					fcppt::optional::to_container<
						awl::event::container
					>(
						fcppt::optional::make_if(
							awl::timer::match(
								_event,
								_timer
							),
							[
								&_window
							]{
								return
									fcppt::unique_ptr_to_base<
										awl::event::base
									>(
										fcppt::make_unique_ptr<
											sge::renderer::event::render
										>(
											fcppt::make_ref(
												_window
											)
										)
									);
							}
						)
					);
			}
		};
}
