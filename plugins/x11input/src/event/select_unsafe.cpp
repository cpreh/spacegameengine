//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/exception.hpp>
#include <sge/x11input/device/id.hpp>
#include <sge/x11input/event/select_unsafe.hpp>
#include <sge/x11input/event/type.hpp>
#include <sge/x11input/event/type_container.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/window/base.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/array/init_const.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XI2.h>
#include <X11/extensions/XInput2.h>
#include <array>
#include <fcppt/config/external_end.hpp>


void
sge::x11input::event::select_unsafe(
	awl::backends::x11::window::base const &_window,
	sge::x11input::device::id const _device,
	sge::x11input::event::type_container const &_types
)
{
	if(
		_window.destroyed()
	)
		return;

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)
FCPPT_PP_DISABLE_GCC_WARNING(-Wconversion)
	typedef
	std::array<
		unsigned char,
		XIMaskLen(XI_LASTEVENT)
	>
	mask_type;
FCPPT_PP_POP_WARNING

	mask_type mask_data(
		fcppt::container::array::init_const<
			mask_type
		>(
			fcppt::literal<
				unsigned char
			>(
				0
			)
		)
	);

	for(
		sge::x11input::event::type const &event
		:
		_types
	)
	FCPPT_PP_PUSH_WARNING
	FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)
	FCPPT_PP_DISABLE_GCC_WARNING(-Wconversion)
		XISetMask(
			mask_data.data(),
			event.get()
		);
	FCPPT_PP_POP_WARNING

	XIEventMask mask{
		_device.get(),
		mask_data.size(),
		mask_data.data()
	};

	if(
		::XISelectEvents(
			_window.display().get(),
			_window.get(),
			&mask,
			1
		)
		!= 0
	)
		throw
			sge::input::exception{
				FCPPT_TEXT("XISelectEvents failed!")
			};
}
