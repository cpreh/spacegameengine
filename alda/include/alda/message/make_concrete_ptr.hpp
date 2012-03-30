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


#ifndef ALDA_MESSAGE_MAKE_CONCRETE_PTR_HPP_INCLUDED
#define ALDA_MESSAGE_MAKE_CONCRETE_PTR_HPP_INCLUDED

#include <alda/message/base_unique_ptr.hpp>
#include <alda/message/concrete_decl.hpp>
#include <fcppt/make_unique_ptr.hpp>


namespace alda
{
namespace message
{

template<
	typename TypeEnum,
	typename Message
>
typename alda::message::base_unique_ptr<
	TypeEnum
>::type
make_concrete_ptr(
	Message const &_value
)
{
	return
		typename alda::message::base_unique_ptr<
			TypeEnum
		>::type(
			fcppt::make_unique_ptr<
				alda::message::concrete<
					TypeEnum,
					Message
				>
			>(
				_value
			)
		);
}

}
}

#endif
