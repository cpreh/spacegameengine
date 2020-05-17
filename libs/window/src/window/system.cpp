//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/window/event_combiner.hpp>
#include <sge/window/system.hpp>
#include <sge/window/system_event_function.hpp>
#include <awl/event/base.hpp>
#include <awl/event/container.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/system/object.hpp>
#include <awl/system/reference.hpp>
#include <awl/system/event/processor.hpp>
#include <awl/system/event/result.hpp>
#include <fcppt/algorithm/map_concat.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::window::system::system(
	awl::system::reference const _awl_system
)
:
	awl_system_{
		_awl_system
	},
	event_signal_{
		event_signal::combiner_function{
			sge::window::event_combiner
		}
	}
{
}

sge::window::system::~system()
= default;

awl::system::event::result
sge::window::system::poll()
{
	return
		this->transform_events(
			this->awl_system().processor().poll()
		);
}

awl::system::event::result
sge::window::system::next()
{
	return
		this->transform_events(
			this->awl_system().processor().next()
		);
}

void
sge::window::system::quit(
	awl::main::exit_code const _exit_code
)
{
	this->awl_system().processor().quit(
		_exit_code
	);
}

fcppt::signal::auto_connection
sge::window::system::event_handler(
	sge::window::system_event_function &&_function
)
{
	return
		event_signal_.connect(
			std::move(
				_function
			)
		);
}

awl::system::object &
sge::window::system::awl_system()
{
	return
		awl_system_.get();
}

awl::system::event::result
sge::window::system::transform_events(
	awl::system::event::result &&_result
)
{
	return
		fcppt::either::match(
			std::move(
				_result
			),
			[](
				awl::main::exit_code const _code
			)
			{
				return
					awl::system::event::result{
						_code
					};
			},
			[
				this
			](
				awl::event::container &&_events
			)
			{
				auto new_events(
					fcppt::algorithm::map_concat<
						awl::event::container
					>(
						_events,
						[
							this
						](
							awl::event::base_unique_ptr const &_event
						)
						{
							return
								event_signal_(
									event_signal::initial_value{
										awl::event::container{}
									},
									*_event
								);
						}
					)
				);

				return
					awl::system::event::result{
						fcppt::container::join(
							std::move(
								_events
							),
							std::move(
								new_events
							)
						)
					};
			}
		);
}
