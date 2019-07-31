//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_JOYPAD_FF_WAVEFORM_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_FF_WAVEFORM_HPP_INCLUDED

#include <sge/input/joypad/ff/waveform_fwd.hpp>


namespace sge
{
namespace input
{
namespace joypad
{
namespace ff
{

enum class waveform
{
	square,
	triangle,
	sine,
	saw_up,
	saw_down
};

}
}
}
}

#endif
