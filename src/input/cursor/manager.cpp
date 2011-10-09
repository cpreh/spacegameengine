/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/input/cursor/manager.hpp>
#include <sge/input/cursor/discover_callback.hpp>
#include <sge/input/cursor/discover_event.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/object_vector.hpp>
#include <sge/input/cursor/remove_callback.hpp>
#include <sge/input/cursor/remove_event.hpp>
#include <sge/input/processor.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/signal/shared_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_unique_ptr.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::input::cursor::manager::manager(
	input::processor &_processor,
	input::cursor::discover_callback const &_discover_callback,
	input::cursor::remove_callback const &_remove_callback,
	button_callback const &_button_callback,
	move_callback const &_move_callback
)
:
	objects_(),
	discover_callback_(
		_discover_callback
	),
	remove_callback_(
		_remove_callback
	),
	button_callback_(
		_button_callback
	),
	move_callback_(
		_move_callback
	),
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::connection_manager::container
		>(
			fcppt::signal::shared_connection(
				_processor.cursor_discover_callback(
					std::tr1::bind(
						&cursor::manager::discover,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				_processor.cursor_remove_callback(
					std::tr1::bind(
						&cursor::manager::remove,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
	)
{
	cursor::object_vector const objects(
		_processor.cursors()
	);

	for(
		cursor::object_vector::const_iterator it(
			objects.begin()
		);
		it != objects.end();
		++it
	)
		this->discover(
			input::cursor::discover_event(
				*it
			)
		);
}
FCPPT_PP_POP_WARNING

sge::input::cursor::manager::~manager()
{
}

void
sge::input::cursor::manager::discover(
	input::cursor::discover_event const &_event
)
{
	FCPPT_ASSERT_ERROR(
		fcppt::container::ptr::insert_unique_ptr_map(
			objects_,
			_event.object(),
			fcppt::make_unique_ptr<
				fcppt::signal::connection_manager
			>(
				fcppt::assign::make_container<
					fcppt::signal::connection_manager::container
				>(
					fcppt::signal::shared_connection(
						_event.object()->button_callback(
							std::tr1::bind(
								button_callback_,
								_event.object(),
								std::tr1::placeholders::_1
							)
						)
					)
				)
				(
					fcppt::signal::shared_connection(
						_event.object()->move_callback(
							std::tr1::bind(
								move_callback_,
								_event.object(),
								std::tr1::placeholders::_1
							)
						)
					)
				)
			)
		).second
		== true
	);

	if(
		discover_callback_
	)
		discover_callback_(
			_event
		);
}

void
sge::input::cursor::manager::remove(
	input::cursor::remove_event const &_event
)
{
	FCPPT_ASSERT_ERROR(
		objects_.erase(
			_event.object()
		)
		== 1u
	);

	if(
		remove_callback_
	)
		remove_callback_(
			_event
		);
}
