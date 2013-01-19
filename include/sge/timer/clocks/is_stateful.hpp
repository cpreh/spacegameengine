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


#ifndef SGE_TIMER_CLOCKS_IS_STATEFUL_HPP_INCLUDED
#define SGE_TIMER_CLOCKS_IS_STATEFUL_HPP_INCLUDED

#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/chrono/system_clocks.hpp>
#include <boost/mpl/or.hpp>
#include <boost/utility/enable_if.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace timer
{
namespace clocks
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Clock,
	typename Enable = void
>
struct is_stateful
:
std::true_type
{
};

template<
	typename Clock
>
struct is_stateful<
	Clock,
	typename boost::enable_if<
		boost::mpl::or_<
			std::is_same<
				boost::chrono::high_resolution_clock,
				Clock
			>,
			std::is_same<
				boost::chrono::steady_clock,
				Clock
			>,
			std::is_same<
				boost::chrono::system_clock,
				Clock
			>
		>
	>::type
>
:
std::false_type
{
};

FCPPT_PP_POP_WARNING

}
}
}

#endif
