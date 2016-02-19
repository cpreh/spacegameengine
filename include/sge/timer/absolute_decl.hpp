/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_TIMER_ABSOLUTE_DECL_HPP_INCLUDED
#define SGE_TIMER_ABSOLUTE_DECL_HPP_INCLUDED

#include <sge/timer/absolute_fwd.hpp>
#include <sge/timer/clocks/detail/wrapper.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace sge
{
namespace timer
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Clock
>
class absolute final
:
	sge::timer::clocks::detail::wrapper<
		Clock
	>
{
	FCPPT_NONCOPYABLE(
		absolute
	);

	typedef
	sge::timer::clocks::detail::wrapper<
		Clock
	>
	base;
public:
	typedef
	Clock
	clock_type;

	typedef
	typename
	clock_type::time_point
	time_point;

	typedef
	typename
	clock_type::duration
	duration;

	absolute();

	explicit
	absolute(
		Clock const &
	);

	time_point
	now() const;

	time_point
	last_time() const;

	void
	reset();
private:
	time_point last_time_;
};

FCPPT_PP_POP_WARNING

}
}

#endif
