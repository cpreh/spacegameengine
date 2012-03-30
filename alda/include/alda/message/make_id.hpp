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


#ifndef ALDA_MESSAGE_MAKE_ID_HPP_INCLUDED
#define ALDA_MESSAGE_MAKE_ID_HPP_INCLUDED

#include <alda/message/id_binding.hpp>
#include <alda/message/roles/type.hpp>
#include <alda/serialization/detail/message_int_type.hpp>
#include <majutsu/constant.hpp>
#include <majutsu/role.hpp>


namespace alda
{
namespace message
{

template<
	typename EnumType,
	typename EnumType::type MessageType
>
struct make_id
{
	typedef majutsu::role<
		majutsu::constant<
			alda::message::id_binding,
			static_cast<
				alda::serialization::detail::message_int_type
			>(
				MessageType
			)
		>,
		alda::message::roles::type
	> type;
};

}
}

#endif
