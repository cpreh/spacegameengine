/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_TIMER_FRAMES_COUNTER_HPP_INCLUDED
#define SGE_TIMER_FRAMES_COUNTER_HPP_INCLUDED

#include <sge/timer/basic_decl.hpp>
#include <sge/timer/frames_counter_fwd.hpp>
#include <sge/timer/symbol.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>


namespace sge
{
namespace timer
{

class frames_counter
{
	FCPPT_NONCOPYABLE(
		frames_counter
	);
public:
	typedef
	sge::timer::clocks::standard
	clock;

	typedef
	unsigned long
	counter;

	SGE_TIMER_SYMBOL
	frames_counter();

	SGE_TIMER_SYMBOL
	void
	update();

	SGE_TIMER_SYMBOL
	counter
	frames() const;

	SGE_TIMER_SYMBOL
	fcppt::string
	frames_str() const;

	SGE_TIMER_SYMBOL
	~frames_counter();
private:
	sge::timer::basic<
		clock
	> timer_;

	counter current_frames_;

	counter display_frames_;
};

}
}

#endif
