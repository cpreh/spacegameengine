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


#ifndef SGE_TIMER_PARAMETERS_DECL_HPP_INCLUDED
#define SGE_TIMER_PARAMETERS_DECL_HPP_INCLUDED

#include <sge/timer/parameters_fwd.hpp>

namespace sge
{
namespace timer
{
template<typename Clock>
class parameters
{
public:
	typedef
	Clock
	clock_type;

	typedef typename
	Clock::duration
	duration;

	template<typename Duration>
	explicit
	parameters(
		clock_type const &,
		Duration const &);

	parameters &
	active(
		bool);

	parameters &
	expired(
		bool);

	duration const
	interval() const;

	clock_type const &
	clock() const;

	bool
	active() const;

	bool
	expired() const;
private:
	clock_type const &clock_;
	duration interval_;
	bool active_;
	bool expired_;
};
}
}

#endif
