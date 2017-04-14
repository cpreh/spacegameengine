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


#include <sge/input/exception.hpp>
#include <sge/x11input/device/event_added.hpp>
#include <sge/x11input/device/select_events.hpp>
#include <awl/backends/x11/deleter.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <fcppt/const.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/algorithm/find_if_opt.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/math/ceil_div.hpp>
#include <fcppt/optional/deref.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/reference.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <algorithm>
#include <cstddef>
#include <limits>
#include <vector>
#include <fcppt/config/external_end.hpp>


void
sge::x11input::device::select_events(
	awl::backends::x11::window::object const &_window,
	sge::x11input::device::id const _device,
	awl::backends::x11::system::event::type const _type,
	sge::x11input::device::event_added const _add
)
{
	if(
		_window.destroyed()
	)
		return;
	// Warning: The following code is crap so I commented it.
	//
	// XI2 stores event masks per device and for all devices separately.
	// sge will add or remove one event type for a device at a time
	// because it does this lazily inside the event demuxers.

	typedef
	fcppt::unique_ptr<
		XIEventMask,
		awl::backends::x11::deleter
	>
	scoped_event_mask;

	int num_masks;

	// We have to extract all masks that we already set first.
	// If there is no such mask, the result will be a null pointer
	// and num_masks will be 0.
	scoped_event_mask const mask(
		::XIGetSelectedEvents(
			_window.display().get(),
			_window.get(),
			&num_masks
		)
	);

	if(
		num_masks == -1
	)
		throw
			sge::input::exception{
				FCPPT_TEXT("XIGetSelectedEvents() failed!")
			};

	typedef
	std::vector<
		XIEventMask
	>
	event_mask_vector;

	// Copy all masks over because we might need to add a new mask.
	event_mask_vector event_masks(
		mask.get_pointer(),
		mask.get_pointer()
		+ num_masks
	);

	// Look if there is already a mask for this device.
	// If there is, we have to update it.
	fcppt::optional::reference<
		XIEventMask
	> prev_mask(
		fcppt::optional::deref(
			fcppt::algorithm::find_if_opt(
				event_masks,
				[
					_device
				](
					XIEventMask const &_mask
				)
				{
					return
						_device.get()
						==
						_mask.deviceid;
				}
			)
		)
	);

	typedef
	unsigned char
	bit_type;

	typedef
	std::vector<
		bit_type
	>
	raw_container;

	// This is the size of the mask buffer that
	// is needed for the new event type only.
	// The event corresponds to the nth bit that will be set.
	raw_container::size_type const least_size(
		fcppt::math::ceil_div(
			fcppt::cast::size<
				raw_container::size_type
			>(
				fcppt::cast::to_unsigned(
					_type.get()
				)
			),
			fcppt::cast::size<
				raw_container::size_type
			>(
				fcppt::cast::to_unsigned(
					std::numeric_limits<
						bit_type
					>::digits
				)
			)
		)
	);

	raw_container store(
		fcppt::optional::maybe(
			prev_mask,
			fcppt::const_(
				least_size
			),
			[
				least_size
			](
				fcppt::reference<
					XIEventMask
				> const _mask
			)
			{
				return
					std::max(
						least_size,
						fcppt::cast::size<
							raw_container::size_type
						>(
							fcppt::cast::to_unsigned(
								_mask.get().mask_len
							)
						)
					);
			}
		),
		fcppt::literal<
			bit_type
		>(
			0
		)
	);

	fcppt::optional::maybe(
		prev_mask,
		// If there is no previous mask,
		// push back a new one.
		[
			&event_masks,
			&store,
			_device
		]{
			event_masks.push_back(
				XIEventMask{
					_device.get(),
					fcppt::cast::size<
						int
					>(
						fcppt::cast::to_signed(
							store.size()
						)
					),
					store.data()
				}
			);
		},
		// Otherwise copy the old mask over,
		// and reset its store.
		[
			&store
		](
			fcppt::reference<
				XIEventMask
			> const _mask
		)
		{
			std::copy_n(
				_mask.get().mask,
				_mask.get().mask_len,
				store.data()
			);

			_mask.get().mask =
				store.data();

			_mask.get().mask_len =
				fcppt::cast::size<
					int
				>(
					fcppt::cast::to_signed(
						store.size()
					)
				);
		}
	);

	if(
		_add.get()
	)
FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)
FCPPT_PP_DISABLE_GCC_WARNING(-Wconversion)
		XISetMask(
			store.data(),
			_type.get()
		);
	else

		XIClearMask(
			store.data(),
			_type.get()
		);
FCPPT_PP_POP_WARNING
	if(
		::XISelectEvents(
			_window.display().get(),
			_window.get(),
			event_masks.data(),
			fcppt::cast::size<
				int
			>(
				fcppt::cast::to_signed(
					event_masks.size()
				)
			)
		)
		!= Success
	)
		throw
			sge::input::exception{
				FCPPT_TEXT("XISelectEvents failed!")
			};
}
