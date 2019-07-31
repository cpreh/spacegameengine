//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/dinput/create_dinput.hpp>
#include <sge/dinput/di.hpp>
#include <sge/dinput/dinput_unique_ptr.hpp>
#include <sge/input/exception.hpp>
#include <awl/backends/windows/module_handle.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/from_void_ptr.hpp>


sge::dinput::dinput_unique_ptr
sge::dinput::create_dinput()
{
	LPVOID ret(
		nullptr
	);

	if(
		::DirectInput8Create(
			awl::backends::windows::module_handle(),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			&ret,
			nullptr
		)
		!= DI_OK
	)
		throw sge::input::exception(
			FCPPT_TEXT("Cannot create DirectInput!")
		);

	return
		sge::dinput::dinput_unique_ptr(
			fcppt::cast::from_void_ptr<
				IDirectInput8 *
			>(
				ret
			)
		);
}
