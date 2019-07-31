//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/dinput/cast_key.hpp>
#include <sge/dinput/di.hpp>


DWORD
sge::dinput::cast_key(
	LONG const _key
)
{
	return
		static_cast<
			DWORD
		>(
			_key
		);
}
