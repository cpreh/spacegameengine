//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/processor.hpp>
#include <sge/input/processor_ref.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/input/cursor/event/move.hpp>
#include <sge/input/cursor/relative_movement/difference.hpp>
#include <sge/input/cursor/relative_movement/event.hpp>
#include <sge/input/impl/cursor/relative_movement/detail/object.hpp>
#include <sge/window/event_function.hpp>
#include <sge/window/object.hpp>
#include <awl/event/base.hpp>
#include <awl/event/container.hpp>
#include <awl/window/event/base.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/optional/apply.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/optional/to_container.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::input::cursor::relative_movement::detail::object::object(
	sge::input::processor_ref const _processor
)
:
	positions_{
		fcppt::algorithm::map<
			position_map
		>(
			_processor.get().cursors(),
			[](
				sge::input::cursor::shared_ptr const &_cursor
			)
			{
				return
					std::make_pair(
						_cursor,
						_cursor->position()
					);
			}
		)
	},
	connection_{
		_processor.get().window().event_handler(
			sge::window::event_function{
				[
					this
				](
					awl::window::event::base const &_event
				)
				->
				awl::event::container
				{
					return
						this->on_event(
							_event
						);
				}
			}
		)
	}
{
}

FCPPT_PP_POP_WARNING

sge::input::cursor::relative_movement::detail::object::~object()
= default;

awl::event::container
sge::input::cursor::relative_movement::detail::object::on_event(
	awl::window::event::base const &_event
)
{
	return
		fcppt::optional::to_container<
			awl::event::container
		>(
			fcppt::optional::bind(
				fcppt::cast::dynamic<
					sge::input::cursor::event::move const
				>(
					_event
				),
				[
					this
				](
					fcppt::reference<
						sge::input::cursor::event::move const
					> const _move_event
				)
				{
					return
						fcppt::optional::map(
							this->update_pos(
								_move_event.get()
							),
							[
								_move_event
							](
								sge::input::cursor::relative_movement::difference const &_difference
							)
							{
								return
									fcppt::unique_ptr_to_base<
										awl::event::base
									>(
										fcppt::make_unique_ptr<
											sge::input::cursor::relative_movement::event
										>(
											_move_event.get().cursor(),
											_difference
										)
									);

							}
						);
				}
			)
		);
}

sge::input::cursor::relative_movement::detail::object::optional_difference
sge::input::cursor::relative_movement::detail::object::update_pos(
	sge::input::cursor::event::move const &_move_event
)
{
	optional_difference difference{
		fcppt::optional::apply(
			[](
				sge::input::cursor::position const &_old_pos,
				sge::input::cursor::position const &_new_pos
			)
			{
				return
					sge::input::cursor::relative_movement::difference{
						_old_pos
						-
						_new_pos
					};
			},
			this->positions_[
				_move_event.cursor()
			],
			_move_event.position()
		)
	};

	this->positions_[
		_move_event.cursor()
	] =
		_move_event.position();

	return
		difference;
}
