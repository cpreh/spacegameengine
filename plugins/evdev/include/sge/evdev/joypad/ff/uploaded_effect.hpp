//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_JOYPAD_FF_UPLOADED_EFFECT_HPP_INCLUDED
#define SGE_EVDEV_JOYPAD_FF_UPLOADED_EFFECT_HPP_INCLUDED

#include <sge/evdev/device/fd_fwd.hpp>
#include <sge/evdev/joypad/ff/id.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace evdev
{
namespace joypad
{
namespace ff
{

class uploaded_effect
{
	FCPPT_NONCOPYABLE(
		uploaded_effect
	);
public:
	uploaded_effect(
		sge::evdev::device::fd const &,
		ff_effect
	);

	~uploaded_effect();

	sge::evdev::joypad::ff::id
	id() const;
private:
	sge::evdev::device::fd const &fd_;

	ff_effect effect_;
};

}
}
}
}

#endif
