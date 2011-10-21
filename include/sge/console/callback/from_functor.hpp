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


#ifndef SGE_CONSOLE_CALLBACK_FROM_FUNCTOR_HPP_INCLUDED
#define SGE_CONSOLE_CALLBACK_FROM_FUNCTOR_HPP_INCLUDED

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
template<typename FunctionType,typename Functor>
callback::parameters
from_functor(
	Functor const &_f,
	callback::name const &_name,
	callback::short_description const &_short_description)
{
	return
		callback::parameters(
			detail::convenience_wrapper<FunctionType>(
				_f,
				_short_description.get()),
			_name)
			.short_description(
				_short_description.get());
}
}
}
}

#endif
