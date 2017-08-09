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


#include <sge/dinput/is_down.hpp>
#include <sge/dinput/keyboard/device.hpp>
#include <sge/dinput/keyboard/key_map.hpp>
#include <sge/dinput/keyboard/make_info.hpp>
#include <sge/input/key/code.hpp>
#include <sge/input/key/pressed.hpp>
#include <sge/input/keyboard/key.hpp>
#include <sge/input/keyboard/key_id.hpp>
#include <sge/input/keyboard/event/key.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/event/base.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <fcppt/const.hpp>
#include <fcppt/enable_shared_from_this_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/optional/copy_value.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::dinput::keyboard::device::device(
	dinput::device::parameters const &_parameters
)
:
	sge::input::keyboard::device{},
	sge::dinput::device::object{
		_parameters,
		c_dfDIKeyboard
	},
	fcppt::enable_shared_from_this<
		sge::dinput::keyboard::device
	>{},
	info_{
		sge::dinput::keyboard::make_info(
			this->get()
		)
	}
{
}

FCPPT_PP_POP_WARNING

sge::dinput::keyboard::device::~device()
{
}

sge::window::object &
sge::dinput::keyboard::device::window() const
{
	return
		this->sge_window();
}

awl::event::optional_base_unique_ptr
sge::dinput::keyboard::device::on_dispatch(
	DIDEVICEOBJECTDATA const &_data
)
{
	DWORD const offset(
		_data.dwOfs
	);

	sge::input::key::pressed const key_value{
		sge::dinput::is_down(
			_data.dwData
		)
	};

	sge::input::keyboard::key const key{
		fcppt::optional::from(
			fcppt::optional::copy_value(
				fcppt::container::find_opt_mapped(
					info_.key_map(),
					offset
				)
			),
			fcppt::const_(
				sge::input::key::code::unknown
			)
		),
		fcppt::strong_typedef_construct_cast<
			sge::input::keyboard::key_id,
			fcppt::cast::size_fun
		>(
			offset
		)
	};

	return
		awl::event::optional_base_unique_ptr{
			fcppt::unique_ptr_to_base<
				awl::event::base
			>(
				fcppt::make_unique_ptr<
					sge::input::keyboard::event::key
				>(
					this->fcppt_shared_from_this(),
					key,
					key_value
				)
			)
		};
}
