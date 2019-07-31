//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_DINPUT_KEYBOARD_INFO_HPP_INCLUDED
#define SGE_DINPUT_KEYBOARD_INFO_HPP_INCLUDED

#include <sge/dinput/keyboard/info_fwd.hpp>
#include <sge/dinput/keyboard/key_map.hpp>


namespace sge
{
namespace dinput
{
namespace keyboard
{

class info
{
public:
	explicit
	info(
		sge::dinput::keyboard::key_map const &
	);

	sge::dinput::keyboard::key_map const &
	key_map() const;
private:
	sge::dinput::keyboard::key_map key_map_;
};

}
}
}

#endif
