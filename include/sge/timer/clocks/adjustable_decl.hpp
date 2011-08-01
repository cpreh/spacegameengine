/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_TIMER_CLOCKS_ADJUSTABLE_DECL_HPP_INCLUDED
#define SGE_TIMER_CLOCKS_ADJUSTABLE_DECL_HPP_INCLUDED

#include <sge/timer/clocks/adjustable_fwd.hpp>
#include <fcppt/chrono/time_point_decl.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace timer
{
namespace clocks
{
template<typename ClockImpl>
class adjustable
{
FCPPT_NONCOPYABLE(
	adjustable);
public:
	typedef typename
	ClockImpl::rep
	rep;

	typedef typename
	ClockImpl::period
	period;

	typedef typename
	ClockImpl::duration
	duration;

	typedef typename
	ClockImpl::time_point
	time_point;

	typedef
	float
	float_type;

	static bool const is_steady = 
		true;

	adjustable();

	~adjustable();

	void
	update();

	float_type
	factor() const;

	void	
	factor(
		float_type);

	time_point
	now() const;
private:
	time_point current_time_;
	time_point transformed_time_;
	float_type factor_;
};
}
}
}

#endif
