//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/dinput/keyboard/info.hpp>
#include <sge/dinput/keyboard/key_map.hpp>


sge::dinput::keyboard::info::info(
	sge::dinput::keyboard::key_map const &_key_map
)
:
	key_map_(
		_key_map
	)
{
}

sge::dinput::keyboard::key_map const &
sge::dinput::keyboard::info::key_map() const
{
	return
		key_map_;
}
