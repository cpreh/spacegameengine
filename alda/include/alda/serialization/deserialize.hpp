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


#ifndef ALDA_SERIALIZATION_DESERIALIZE_HPP_INCLUDED
#define ALDA_SERIALIZATION_DESERIALIZE_HPP_INCLUDED

#include <alda/exception.hpp>
#include <alda/message/base_unique_ptr.hpp>
#include <alda/serialization/context_decl.hpp>
#include <alda/serialization/istream.hpp>
#include <alda/serialization/detail/message_int_type.hpp>
#include <alda/serialization/detail/dispatch/base_decl.hpp>
#include <alda/serialization/detail/dispatch/map.hpp>
#include <alda/serialization/detail/read/object_decl.hpp>
#include <fcppt/static_assert_expression.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/throw.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <iosfwd>
#include <istream>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace serialization
{

template<
	typename TypeEnum
>
typename alda::message::base_unique_ptr<
	TypeEnum
>::type
deserialize(
	alda::serialization::context<
		TypeEnum
	> const &_context,
	alda::serialization::istream &_stream
)
{
	typedef typename TypeEnum::type message_type;

	// TODO: we can't specify the endianness of the message type at the moment
	FCPPT_STATIC_ASSERT_EXPRESSION(
		sizeof(
			alda::serialization::detail::message_int_type
		)
		== 1u
	);

	alda::serialization::detail::message_int_type type;

	// TODO: fix endianness here
	_stream.read(
		reinterpret_cast<
			char *
		>(
			&type
		),
		static_cast<
			std::streamsize
		>(
			sizeof(
				alda::serialization::detail::message_int_type
			)
		)
	);

	FCPPT_ASSERT_THROW(
		static_cast<
			std::size_t
		>(
			_stream.gcount()
		)
		==
		sizeof(
			alda::serialization::detail::message_int_type
		),
		alda::exception
	);

	_stream.unget();

	if(
		type
		>=
		static_cast<
			alda::serialization::detail::message_int_type
		>(
			TypeEnum::size::value
		)
	)
		throw alda::exception(
			FCPPT_TEXT("Invalid message received!")
		);

	message_type const casted_type(
		static_cast<
			message_type
		>(
			type
		)
	);

	typedef typename alda::serialization::detail::dispatch::map<
		TypeEnum
	>::type dispatch_map;

	typename dispatch_map::const_iterator const it(
		_context.handlers().find(
			casted_type
		)
	);

	if(
		it == _context.handlers().end()
	)
		throw alda::exception(
			FCPPT_TEXT("No handler for a message found.")
		);

	typedef alda::serialization::detail::read::object<
		TypeEnum
	> reader;

	reader cur_reader(
		_stream
	);

	return
		it->second->on_dispatch(
			cur_reader
		);
}

}
}

#endif
