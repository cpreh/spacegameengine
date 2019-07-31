//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/dinput/di.hpp>
#include <sge/dinput/joypad/ff/scoped_download.hpp>
#include <sge/input/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>


sge::dinput::joypad::ff::scoped_download::scoped_download(
	IDirectInputEffect &_effect
)
:
	effect_{
		_effect
	}
{
	switch(
		effect_.Download()
	)
	{
	case DI_OK:
		return;
	case
	static_cast<
		HRESULT
	>(
		DIERR_DEVICEFULL
	):
		throw
			sge::input::exception{
				FCPPT_TEXT("FF device is full!")
			};
	default:
		throw
			sge::input::exception{
				FCPPT_TEXT("Failed downloading an effect!")
			};
	}
}

sge::dinput::joypad::ff::scoped_download::~scoped_download()
{
	FCPPT_ASSERT_ERROR(
		effect_.Unload()
		==
		DI_OK
	);
}
