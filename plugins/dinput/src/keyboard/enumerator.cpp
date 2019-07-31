//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/dinput/di.hpp>
#include <sge/dinput/device/enumerator.hpp>
#include <sge/dinput/keyboard/enumerator.hpp>
#include <sge/dinput/keyboard/key_map.hpp>
#include <sge/dinput/keyboard/translate_key_code.hpp>


sge::dinput::keyboard::enumerator::enumerator()
:
	sge::dinput::device::enumerator(),
	key_map_()
{
}

sge::dinput::keyboard::enumerator::~enumerator()
{
}

sge::dinput::keyboard::key_map const &
sge::dinput::keyboard::enumerator::key_map() const
{
	return
		key_map_;
}

void
sge::dinput::keyboard::enumerator::dispatch(
	DIDEVICEOBJECTINSTANCE const &_data
)
{
	if(
		_data.guidType != GUID_Key
	)
		return;

	key_map_[
		_data.dwOfs
	] =
		sge::dinput::keyboard::translate_key_code(
			_data.dwOfs
		);
}
