/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef ALDA_CALL_DETAIL_CONCRETE_IMPL_HPP_INCLUDED
#define ALDA_CALL_DETAIL_CONCRETE_IMPL_HPP_INCLUDED

#include <alda/call/detail/base_decl.hpp>
#include <alda/call/detail/concrete_decl.hpp>
#include <alda/message/base_fwd.hpp>
#include <alda/message/concrete_decl.hpp>


template<
	typename TypeEnum,
	typename Callee,
	typename Message
>
alda::call::detail::concrete<
	TypeEnum,
	Callee,
	Message
>::concrete()
:
	base_type()
{
}

template<
	typename TypeEnum,
	typename Callee,
	typename Message
>
alda::call::detail::concrete<
	TypeEnum,
	Callee,
	Message
>::~concrete()
{
}

template<
	typename TypeEnum,
	typename Callee,
	typename Message
>
typename Callee::result_type
alda::call::detail::concrete<
	TypeEnum,
	Callee,
	Message
>::call(
	Callee &_callee,
	message_type const &_message
) const
{
	return
		_callee(
			// TODO: static_cast
			dynamic_cast<
				alda::message::concrete<
					TypeEnum,
					Message
				> const &
			>(
				_message
			).value()
		);
}

#endif
