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


#ifndef ALDA_SERIALIZATION_REGISTER_MESSAGE_HPP_INCLUDED
#define ALDA_SERIALIZATION_REGISTER_MESSAGE_HPP_INCLUDED

#include <alda/serialization/detail/dispatch/register_impl.hpp>


#define ALDA_SERIALIZATION_REGISTER_MESSAGE(\
	context,\
	type_enum,\
	message_type\
)\
\
alda::serialization::detail::dispatch::register_<\
	type_enum,\
	message_type\
> const \
register_class_tmp(\
	context\
)\

#endif
