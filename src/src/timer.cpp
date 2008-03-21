/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../timer.hpp"

sge::timer::timer(
	const interval_type interval_,
	const bool active_)
: interval_(interval_),
  last_time_(time()),
  active_(active_)
{}

sge::timer::frames_type sge::timer::update()
{
	if(!active())
		return 0;

	const frames_type f = elapsed_frames();
	if(f >= 1)
		reset();
	return f < 1 ? 0 : f;
}

sge::timer::frames_type sge::timer::elapsed_frames() const
{
	if(!active())
		return 0;

	const interval_type ntime = time(),
	                    dif = ntime - last_time();
	return static_cast<frames_type>(dif) / static_cast<frames_type>(interval());
}

void sge::timer::reset()
{
	last_time_ = time();
}

bool sge::timer::expired() const
{
	return active() && elapsed_frames() >= 1;
}

void  sge::timer::activate()
{
	if(active())
		return;
	reset();
	active_ = true;
}

void sge::timer::deactivate()
{
	active_ = false;
}

sge::timer::interval_type sge::timer::interval() const
{
	return interval_;
}

sge::timer::interval_type sge::timer::last_time() const
{
	return last_time_;
}

bool sge::timer::active() const
{
	return active_;
}

void sge::timer::interval(const interval_type i)
{
	interval_ = i;
	reset();
}
