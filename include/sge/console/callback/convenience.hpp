/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_CONSOLE_CALLBACK_CONVENIENCE_HPP_INCLUDED
#define SGE_CONSOLE_CALLBACK_CONVENIENCE_HPP_INCLUDED

#include <sge/console/callback/function.hpp>
#include <sge/console/callback/name.hpp>
#include <sge/console/callback/parameters.hpp>
#include <sge/console/callback/short_description.hpp>
#include <sge/console/callback/detail/convenience_wrapper.hpp>


namespace sge
{
namespace console
{
namespace callback
{

template<
	typename FunctionType,
	typename Function
>
inline
sge::console::callback::parameters
convenience(
	Function const &_function,
	sge::console::callback::name const &_name,
	sge::console::callback::short_description const &_short_description
)
{
	return
		sge::console::callback::parameters(
			sge::console::callback::function{
				sge::console::callback::detail::convenience_wrapper<
					FunctionType
				>{
					_function,
					_short_description.get()
				}
			},
			_name
		)
		.short_description(
			_short_description.get()
		);
}

}
}
}

#endif
