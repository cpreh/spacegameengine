/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/input/focus/count.hpp>
#include <sge/input/focus/in_callback.hpp>
#include <sge/input/focus/in_event.hpp>
#include <sge/input/focus/key_callback.hpp>
#include <sge/input/focus/key_event.hpp>
#include <sge/input/focus/mod_state_tracker.hpp>
#include <sge/input/focus/object.hpp>
#include <sge/input/key/modifier.hpp>
#include <sge/input/key/mod_state.hpp>
#include <sge/input/key/to_modifier.hpp>
#include <fcppt/make_enum_range.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/algorithm/enum_array_fold_static.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/cast/to_void.hpp>
#include <fcppt/container/enum_array_impl.hpp>
#include <fcppt/container/bitfield/operators.hpp>


sge::input::focus::mod_state_tracker::mod_state_tracker(
	sge::input::focus::object &_focus
)
:
	counts_(
		sge::input::focus::mod_state_tracker::null_array()
	),
	in_connection_(
		_focus.in_callback(
			sge::input::focus::in_callback(
				[
					this
				](
					sge::input::focus::in_event const &
				)
				{
					counts_ =
						sge::input::focus::mod_state_tracker::null_array();
				}
			)
		)
	),
	key_connection_(
		_focus.key_callback(
			sge::input::focus::key_callback(
				[
					this
				](
					sge::input::focus::key_event const &_event
				)
				{
					fcppt::maybe_void(
						sge::input::key::to_modifier(
							_event.key().code()
						),
						[
							&_event,
							this
						](
							sge::input::key::modifier const _mod
						)
						{
							count &entry(
								counts_[
									_mod
								]
							);

							if(
								_event.pressed()
							)
								++entry;
							else if(
								entry
								!=
								sge::input::focus::count{
									0u
								}
							)
								--entry;
						}
					);
				}
			)
		)
	)
{
}

sge::input::focus::mod_state_tracker::~mod_state_tracker()
{
}

sge::input::key::mod_state
sge::input::focus::mod_state_tracker::mod_state() const
{
	return
		fcppt::algorithm::fold(
			fcppt::make_enum_range<
				sge::input::key::modifier
			>(),
			sge::input::key::mod_state::null(),
			[
				this
			](
				sge::input::key::modifier const _mod,
				sge::input::key::mod_state const _state
			)
			{
				return
					counts_[
						_mod
					]
					!=
					sge::input::focus::count{
						0u
					}
					?
						_state
						|
						_mod
					:
						_state
					;
			}
		);
}

sge::input::focus::mod_state_tracker::count_array
sge::input::focus::mod_state_tracker::null_array()
{
	return
		fcppt::algorithm::enum_array_fold_static<
			count_array
		>(
			[](
				auto const _index
			)
			{
				fcppt::cast::to_void(
					_index
				);

				return
					sge::input::focus::count{
						0u
					};
			}
		);
}
