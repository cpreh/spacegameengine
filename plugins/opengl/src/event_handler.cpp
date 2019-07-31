//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
