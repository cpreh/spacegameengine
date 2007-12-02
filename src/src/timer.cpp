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

sge::timer::timer()
: _interval(1000),
  _last_time(time()),
  _active(false)
{}

sge::timer::timer(const interval_type _interval)
: _interval(_interval),
  _last_time(time()),
  _active(true)
{}

sge::timer::frames_type sge::timer::update()
{
	if(!_active)
		return 0;

	const frames_type f = elapsed_frames();
	if(f >= 1)
		reset();
	return f < 1 ? 0 : f;
}

sge::timer::frames_type sge::timer::elapsed_frames() const
{
	if(!_active)
		return 0;

	const interval_type ntime = time(),
	                    dif = ntime - last_time();
	return static_cast<frames_type>(dif) / interval();
}

void sge::timer::reset()
{
	_last_time = time();
}

bool sge::timer::expired() const
{
	return _active && elapsed_frames() >= 1;
}

void  sge::timer::activate()
{
	reset();
	_active = true;
}

void sge::timer::deactivate()
{
	_active = false;
}

sge::timer::interval_type sge::timer::interval() const
{
	return _interval;
}

sge::timer::interval_type sge::timer::last_time() const
{
	return _last_time;
}

bool sge::timer::active() const
{
	return _active;
}

void sge::timer::interval(const interval_type i)
{
	_interval = i;
	reset();
}
