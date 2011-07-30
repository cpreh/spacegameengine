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


#ifndef SGE_TIMER_CLOCKS_DELTA_DECL_HPP_INCLUDED
#define SGE_TIMER_CLOCKS_DELTA_DECL_HPP_INCLUDED

#include <sge/timer/clocks/delta_fwd.hpp>
#include <fcppt/chrono/time_point_decl.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace timer
{
namespace clocks
{
template<typename Impl>
class delta
{
FCPPT_NONCOPYABLE(
	delta);
public:
	typedef typename
	Impl::period
	period;

	typedef typename
	Impl::duration
	duration;

	typedef typename
	Impl::time_point
	time_point;

	static bool const is_steady = 
		true;

	delta();

	~delta();

	void
	update(
		duration const &);

	time_point
	now() const;
private:
	time_point now_;
};

}
}
}

#endif
